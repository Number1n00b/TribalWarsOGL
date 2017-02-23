#include "Camera.h"
#include <iostream>

Camera::Camera(const glm::vec3& pos, glm::vec3 look_direction, glm::vec3 up_direction, float fov, float aspect, float z_near, float z_far)
{
	m_perspective = glm::perspective(fov, aspect, z_near, z_far);

	m_position = pos;

	m_forward = look_direction;
	m_up = up_direction;

	m_fov = fov;
	m_aspect = aspect;
	m_zNear = z_near;
	m_zFar = z_far;
}

glm::mat4 Camera::GetViewProjection() const{
	return  m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
}

glm::vec3 Camera::GetPosition() {
    return m_position;
}



void Camera::NotifyMouseEvent(SDL_Event e) {
    using std::cout;
    using std::endl;
    switch (e.type) {
    case SDL_MOUSEMOTION:
        cout << "{Camera}: Mouse Moved: (" << e.motion.x << ", " << e.motion.y << ")" << endl;
        break;
    case SDL_MOUSEWHEEL:
        cout << "{Camera}: Mouse wheel: " << e.wheel.direction << endl;
        break;
    case SDL_MOUSEBUTTONDOWN:
        cout << "{Camera}: Mosue clicked: " << e.button.button << endl;
        break;
    case SDL_MOUSEBUTTONUP:
        //Empty
        break;
    default:
        cout << "{Camera}: Unknown mouse event: " << e.type << endl;
    }
}



void Camera::SetPosition(glm::vec3 pos) {
	m_position = pos;
}

void Camera::SetPosition(float x, float y, float z) {
    m_position = glm::vec3(x, y, z);
}


void Camera::SetLookDirection(glm::vec3 look_direction) {
	m_forward = look_direction;
}

void Camera::SetLookDirection(float x, float y, float z) {
    m_forward = glm::vec3(x, y, z);
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

void Camera::SetAspectRatio(float aspect) {
	m_aspect = aspect;
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

