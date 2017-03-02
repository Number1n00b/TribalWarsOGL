#include <iostream>
#include "Camera.h"
#include "Main.h"

Camera::Camera(const glm::vec3& pos, glm::vec3 look_direction, glm::vec3 up_direction, float fov, float aspect, float z_near, float z_far)
{
    m_ZoomFactor = 1;
    
	m_perspective = glm::perspective(fov * m_ZoomFactor, aspect, z_near, z_far);

	m_position = pos;

	m_LookDirection = look_direction;
	m_up = up_direction;

	m_fov = fov;
	m_aspect = aspect;
	m_zNear = z_near;
	m_zFar = z_far;

    m_ReferenceMousePositionX = Window::Window_Width / 2;
    m_ReferenceMousePositionY = Window::Window_Height / 2;

    m_Sensitivity = (1.0 / 70.0);
    m_MouseMoved = false;
    m_CameraWasReset = false;
}

glm::mat4 Camera::GetViewProjection() const{
	return  m_perspective * glm::lookAt(m_position, m_position + m_LookDirection, m_up);
}

glm::vec3 Camera::GetPosition() {
    return m_position;
}

//@Refactor @Cleanup @Move
float clamp(float val, float min, float max) {
    if (val > max) {
        return max;
    }

    if (val < min) {
        return min;
    }

    return val;
}

//@Incomplete @WorkInProgress,
//Currently I have a 180 degree vision. I can see a hemisphere perfectly. The problem comes when setting the z "lookat" direction.
//Im calculating z based on the sphere formula x^2 + y^2 + z^2 = 1, but my x and y can BOTH be one at the same time giving invalid results for z.
//Unsure as of how to proceed for now, in the end I want full 360 degree vision.
void Camera::Update() {
        float sens = 0.035;

        //Keep track of which direction x should be going, starting with increasing to the right. 
        static int x_clip = 1;

        //Multipler for if z needs to be inverted. (i.e looking at the back side of the hemisphere.
        static int z_multiplier = -1;

        if (m_CameraWasReset) {
            x_clip = 1;
            z_multiplier = -1;
            m_CameraWasReset = false;
        }

        if ( m_MouseMoved ) {
            //Map from 2D plane to 3D sphere of radius 1.
            double x = sens * m_MouseMovement.x * x_clip + m_LookDirection.x;
            double y = sens * -m_MouseMovement.y + m_LookDirection.y;

            //Clamp y to maximum value.
            if (y >= 0.95) {
                y = 0.95;
            }
            else if (y <= -0.95) {
                y = -0.95;
            }

            double z = 0;
            
            //std::cout << "1. (" << x << ", " << y << ", " << z << ")" << std::endl;

            //If x and y are in bounds, we can calculate z normally.
            if ((pow(x, 2) + pow(y, 2)) < 1) {
                double x_squared = pow(x, 2);
                double y_squared = pow(y, 2);
                z = sqrt(1 - (x_squared + y_squared) );
                //std::cout << "2. (" << x << ", " << y << ", " << z << ")" << std::endl;
            }
            else {
                //If they are not in bounds, we should map them to their bounds using modulo, then calculate z.
                //To map them to an appropriate coordinate, first consider if they are greater than 1: Meaning we should be looking at the other side of the hemisphere

                //Get x and why to between 0 and 1 again.
                if (x >= 1) {
                    x = 1;
                    x_clip = -x_clip;
                    z_multiplier = -z_multiplier;
                    //std::cout << "3. (" << x << ", " << y << ", " << z << ")" << std::endl;
                }
                else if (x <= -1) {
                    x = -1;
                    x_clip = -x_clip;
                    z_multiplier = -z_multiplier;
                    //std::cout << "4. (" << x << ", " << y << ", " << z << ")" << std::endl;
                }

                //Now, proportionatly scale down x and y to be within range.
                if (pow(x, 2) + pow(y, 2) >= 1) {
                    z = 0;
                    /*
                    int x_mult = 1;
                    int y_mult = 1;
                    if (x > 0) {
                        x_mult = -1;
                    }
                    if (y > 0) {
                        y_mult = -1;
                    }


                    x += x_mult*0.001;
                    y += y_mult*0.001;

                    std::cout << "condition: " << x << ", " << y << std::endl;*/
                    //std::cout << "7. (" << x << ", " << y << ", " << z << ")" << std::endl;
                }
                else {

                    z = sqrt(1 - (pow(x, 2) + pow(x, 2)));
                    //std::cout << "8. (" << x << ", " << y << ", " << z << ")" << std::endl;
                }
            }

            std::cout << "(" << x << ", " << y << ", " << z_multiplier*z << ")" << std::endl;


            m_LookDirection = glm::vec3(x, y, z_multiplier * z);

            //Reset mouse movement so that the cam doesnt move automatically once mouse stops.
            m_MouseMovement = glm::vec3(0, 0, 0);
            m_MouseMoved = false;
        }

        //std::cout << "(" << m_LookDirection.x << ", " << m_LookDirection.y << ", " << m_LookDirection.z << ")" << std::endl;


}

void Camera::NotifyKeyEvent(SDL_Event e) {
    switch (e.type) {
        case SDL_KEYDOWN:
        {
            switch (e.key.keysym.sym) {
            case SDLK_KP_ENTER:
                //@Refactor, this isnt clean as this positio / orientation may not always be the right way.
                m_position = glm::vec3(0, 0, 10);
                m_LookDirection = glm::vec3(0, 0, -1);
                m_up = glm::vec3(0, 1, 0);
                m_CameraWasReset = true;
                break;
            }
            break;
        }
    }
}

void Camera::NotifyMouseEvent(SDL_Event e) {
    using std::cout;
    using std::endl;
    switch (e.type) {
        case SDL_MOUSEMOTION:
        {
            //cout << "{Camera}: Mouse Moved: (" << e.motion.x << ", " << e.motion.y << ")" << endl;
            glm::vec2 relative = glm::vec2(e.motion.x - m_ReferenceMousePositionX, e.motion.y - m_ReferenceMousePositionY);
            m_MouseMovement = glm::normalize(relative);

            m_MouseMoved = true;
            break;
        }
        case SDL_MOUSEWHEEL:
        {
            //cout << "{Camera}: Mouse wheel: " << e.wheel.direction << endl;
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            //cout << "{Camera}: Mosue clicked: " << e.button.button << endl;
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            //Empty
            break;
        }
        default: 
        {
            cout << "{Camera}: Unknown mouse event: " << e.type << endl;
        }
    }
}

void Camera::SetSensitivity(float sens) {
    m_Sensitivity = sens;
}


void Camera::SetPosition(glm::vec3 pos) {
	m_position = pos;
}

void Camera::SetPosition(float x, float y, float z) {
    m_position = glm::vec3(x, y, z);
}


void Camera::SetLookDirection(glm::vec3 look_direction) {
	m_LookDirection = look_direction;
}

void Camera::SetLookDirection(float x, float y, float z) {
    m_LookDirection = glm::vec3(x, y, z);
}

void Camera::SetUpDirection(glm::vec3 up_direction) {
	m_up = up_direction;
}

void Camera::SetUpDirection(float x, float y, float z) {
    m_up = glm::vec3(x, y, z);
}


void Camera::UpdatePerspective() {
	m_perspective = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}

void Camera::SetFOV(float fov) {
	m_fov = fov;
	UpdatePerspective();
}

void Camera::NotifyScreenResize(int width, int height) {
	m_aspect = float(width) / float(height);
    m_ReferenceMousePositionX = width/2;
    m_ReferenceMousePositionY = height/2;
	UpdatePerspective();
}

void Camera::SetZNear(float z_near) {
	m_zNear = z_near;
	UpdatePerspective();
}

void Camera::SetZFar(float z_far) {
	m_zFar = z_far;
	UpdatePerspective();
}

