#include <iostream>
#include "Camera.h"
#include "../main/main.h"
#include "../util/Util.h"

#include "../input/KeyboardListener.h"
#include "../input/InputEventHandler.h"

using std::isnan;

Camera::Camera(const glm::vec3& pos, glm::vec3 look_direction, glm::vec3 up_direction,
               float fov, float aspect, float z_near, float z_far,
               int window_width, int window_height)
{
    m_ZoomFactor = 1;

	m_Perspective = glm::perspective(fov * m_ZoomFactor, aspect, z_near, z_far);

	m_Position = m_StartingPos = pos;
    m_DesiredLookDirection = look_direction;
	m_LookDirection = m_StartingLookDir = look_direction;
	m_up = m_StartingUp = up_direction;

	m_fov = fov;
	m_Aspect = aspect;
	m_zNear = z_near;
	m_zFar = z_far;

    //@Note: Do not modify these, as it causes undefined camera movement behaviour.
    m_ReferenceMousePositionX = window_width / 2;
    m_ReferenceMousePositionY = window_height / 2;

    //Currently useless.
    m_XSensitivity = 0.1;
    m_YSensitivity = 0.1;

    m_MouseMoved = false;

    //Units: m/s
    m_Speed = 5;

    //Units: deg / s
    m_RotSpeed = 420;
}

glm::mat4 Camera::GetViewProjection() const{
	return  m_Perspective * glm::lookAt(m_Position, m_Position + m_LookDirection, m_up);
}

glm::vec3 Camera::GetPosition() {
    return m_Position;
}


void Camera::UpdateRotation(double delta) {
    if (m_MouseMoved) {
        if (!isnan(m_MouseDelta.x) && !isnan(m_MouseDelta.y)) {
            glm::vec3 horizontal_axis = glm::cross(m_LookDirection, m_up);
            glm::vec3 vertical_axis = m_up;

            //Calculate the new look direction.
            //Rotate horizontaly. (About the vertical axis)
            m_DesiredLookDirection = glm::mat3(glm::rotate(-m_MouseDelta.x * m_XSensitivity, vertical_axis)) * m_LookDirection;

            //Rotate vertically. (About the horisontal axis)
            m_DesiredLookDirection = glm::mat3(glm::rotate(-m_MouseDelta.y * m_YSensitivity, horizontal_axis)) * m_DesiredLookDirection;

            //Ensure look direction cannot go over the top, or below the bottom.
            float vertical_angle = Math::angle_deg(m_DesiredLookDirection, vertical_axis);

            //If the angle is out of bounds, dont change the look direction at all.
            if (vertical_angle >= 178 || vertical_angle <= 2) {
                m_DesiredLookDirection = m_LookDirection;
            }

            //Reset mouse movement so that the cam doesnt move automatically once mouse stops.
            m_MouseDelta = glm::vec2(0, 0);
            m_MouseMoved = false;

            glm::vec3 rotation_axis = glm::cross(m_LookDirection, m_DesiredLookDirection);
            using namespace std;

            double degrees = m_RotSpeed * delta / 1000;
            double radians = degrees / 180 * M_PI;
            glm::vec3 new_look_dir = glm::mat3(glm::rotate(float(radians), rotation_axis)) * m_LookDirection;

            if ( !(isnan(new_look_dir.x) || isnan(new_look_dir.y) || isnan(new_look_dir.z)) ) {
                m_LookDirection = new_look_dir;
            }

            //@Debug
            //std::cout << "looking: " << m_LookDirection.x << ", " << m_LookDirection.y << ", " << m_LookDirection.z << std::endl;

        }
        else {
            //@DEBUG
            //std::cout << "MouseDelta was NAN.\n";
        }
    }
}

void Camera::HandleMovement(double delta) {
    glm::vec3 move_dir(0, 0, 0);

    glm::vec3 curr_right = glm::cross(m_LookDirection, m_up);

    //WASD
    if (keys_down[KEY_W]) {
        move_dir += m_LookDirection;
    }
    if (keys_down[KEY_A]) {
        move_dir += -curr_right;
    }
    if (keys_down[KEY_S]) {
        move_dir += -m_LookDirection;
    }
    if (keys_down[KEY_D]) {
        move_dir += curr_right;
    }

    //Up
    if (keys_down[KEY_SPACE]) {
        move_dir += m_up;
    }

    //Down
    if (keys_down[KEY_LSHIFT]) {
        move_dir += -m_up;
    }

    //@FIXME currently if the user is looking 'up' and presses UP and FORWARD at the same time,
    //the effective velocity is doubled. To fix use glm::normalise on move_dir,
    //but for some reason this makes the screen blank atm, so Ill fix it later.
    m_Position += move_dir * float(m_Speed * delta / 1000.0f);
}

void Camera::Update(double delta) {
    HandleMovement(delta);
    UpdateRotation(delta);
}


void Camera::NotifyKeyEvent(SDL_Event e) {
    switch (e.type) {
        case SDL_KEYDOWN:
        {
            switch (e.key.keysym.sym) {
                case SDLK_KP_ENTER:
                {
                    Reset();
                    break;
                }
            }
            break;
        }
    }
}

void Camera::Reset() {
    m_Position = m_StartingPos;

    m_LookDirection = m_StartingLookDir;
    m_DesiredLookDirection = m_StartingLookDir;

    m_up = m_StartingUp;
}

void Camera::NotifyMouseEvent(SDL_Event e) {
    using std::cout;
    using std::endl;
    switch (e.type) {
        case SDL_MOUSEMOTION:
        {
            if (game_state == GAME_STATE::RUNNING) {
                //cout << "{Camera}: Mouse Moved: (" << e.motion.x << ", " << e.motion.y << ")" << endl;
                glm::vec2 relative = glm::vec2(e.motion.x - m_ReferenceMousePositionX, e.motion.y - m_ReferenceMousePositionY);
                m_MouseDelta = glm::normalize(relative);

                m_MouseMoved = true;
            }

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

void Camera::SetXSensitivity(float sens) {
    m_XSensitivity = sens;
}

void Camera::SetYSensitivity(float sens) {
    m_YSensitivity = sens;
}


void Camera::SetPosition(glm::vec3 pos) {
	m_Position = pos;
}

void Camera::SetPosition(float x, float y, float z) {
    m_Position = glm::vec3(x, y, z);
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
	m_Perspective = glm::perspective(m_fov, m_Aspect, m_zNear, m_zFar);
}

void Camera::SetFOV(float fov) {
	m_fov = fov;
	UpdatePerspective();
}

void Camera::NotifyScreenResize(int width, int height) {
	m_Aspect = float(width) / float(height);
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
