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
}

glm::mat4 Camera::GetViewProjection() const{
	return  m_perspective * glm::lookAt(m_position, m_position + m_LookDirection, m_up);
}

glm::vec3 Camera::GetPosition() {
    return m_position;
}

void Camera::Update() {
    m_LookDirection = m_LookDirection + m_MouseMovement;
    //Reset mouse movement so that the cam doesnt move automatically once mouse stops.
    m_MouseMovement = glm::vec3(0, 0, 0);
}

void Camera::NotifyMouseEvent(SDL_Event e) {
    using std::cout;
    using std::endl;
    switch (e.type) {
        case SDL_MOUSEMOTION:
        {
            //cout << "{Camera}: Mouse Moved: (" << e.motion.x << ", " << e.motion.y << ")" << endl;
            glm::vec2 relative = glm::vec2(e.motion.x - m_ReferenceMousePositionX, e.motion.y - m_ReferenceMousePositionY);
            relative = glm::normalize(relative);

            //Save the mouse movement for use in Update().
            m_MouseMovement = glm::vec3(relative.x / (1 / m_Sensitivity), -relative.y / (1 / m_Sensitivity), 0);
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

