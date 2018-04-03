#include <iostream>
#include "Camera.h"

Camera::Camera(const glm::vec3& pos, glm::vec3 look_direction, glm::vec3 up_direction,
               float fov, float aspect, float z_near, float z_far,
               int window_width, int window_height)
{
    m_ZoomFactor = 1;

	m_Perspective = glm::perspective(fov * m_ZoomFactor, aspect, z_near, z_far);

	m_Position = m_StartingPos = pos;
	m_LookDirection = m_StartingLookDir = look_direction;
	m_up = m_StartingUp = up_direction;

	m_fov = fov;
	m_Aspect = aspect;
	m_zNear = z_near;
	m_zFar = z_far;
}

glm::mat4 Camera::GetViewProjection() const{
	return  m_Perspective * glm::lookAt(m_Position, m_Position + m_LookDirection, m_up);
}

glm::vec3 Camera::GetPosition() {
    return m_Position;
}


void Camera::Update(double delta) {
    // Empty
}


void Camera::ResetPositionAndRotation() {
    //Reset position for debug purposes.
    m_Position = m_StartingPos;

    m_LookDirection = m_StartingLookDir;

    m_up = m_StartingUp;
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

Camera::~Camera(){
    //Empty
}
