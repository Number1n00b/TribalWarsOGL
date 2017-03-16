#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 

#include "MouseListener.h"
#include "KeyboardListener.h"

//Camera class @todo finish.
class Camera : public MouseListener, public KeyboardListener
{
	public:
		Camera(const glm::vec3& pos, glm::vec3 look_direction, glm::vec3 up_direction, float fov, float aspect, float z_near, float z_far);

        //Accessors
		glm::mat4 GetViewProjection() const;

        glm::vec3 GetPosition();

		//Mutators
        void SetSensitivity(float sens);

		void SetPosition(glm::vec3 pos);
        void SetPosition(float x, float y, float z);

		void SetLookDirection(glm::vec3 look_direction);
        void SetLookDirection(float x, float y, float z);

        void SetUpDirection(glm::vec3 up_direction);
        void SetUpDirection(float x, float y, float z);

		void SetFOV(float fov);

		void SetZNear(float z_near);
		void SetZFar(float z_far);

        void NotifyMouseEvent(SDL_Event e);
        void NotifyKeyEvent(SDL_Event e);

        void Camera::NotifyScreenResize(int width, int height);

        void Update();

	private:
		//Perspective variables.
		glm::mat4 m_perspective;
		glm::vec3 m_position;
        int m_ReferenceMousePositionX;
        int m_ReferenceMousePositionY;

        float m_Sensitivity;

        float m_ZoomFactor;

		float m_fov;
		float m_aspect;
		float m_zNear;
		float m_zFar;

		glm::vec3 m_LookDirection;
		glm::vec3 m_up;

        glm::vec2 m_MouseMovement;
        bool m_MouseMoved;

        //@Temp @Cleanup
        bool m_CameraWasReset;

		void UpdatePerspective();
};

