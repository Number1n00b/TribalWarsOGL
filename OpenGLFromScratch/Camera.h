#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 

#include "MouseListener.h"

class Camera : public MouseListener
{
	public:
		Camera(const glm::vec3& pos, glm::vec3 look_direction, glm::vec3 up_direction, float fov, float aspect, float z_near, float z_far);

        //Accessors
		glm::mat4 GetViewProjection() const;

        glm::vec3 GetPosition();

		//Mutators
		void SetPosition(glm::vec3 pos);
		void SetLookDirection(glm::vec3 look_direction);
		void SetUpDirection(glm::vec3 up_direction);
		void SetFOV(float fov);
		void SetAspectRatio(float aspect);
		void SetZNear(float z_near);
		void SetZFar(float z_far);

        void NotifyMouseEvent(SDL_Event e);


	private:
		//Perspective variables.
		glm::mat4 m_perspective;
		glm::vec3 m_position;

		float m_fov;
		float m_aspect;
		float m_zNear;
		float m_zFar;

		glm::vec3 m_forward;
		glm::vec3 m_up;

		void UpdatePerspective();
};

