#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../main/main.h"
#include "../util/Util.h"

class Camera
{
	public:
		Camera(const glm::vec3& pos, glm::vec3 look_direction, glm::vec3 up_direction,
		               float fov, float aspect, float z_near, float z_far,
		               int window_width, int window_height);

        //Accessors
		glm::mat4 GetViewProjection() const;

        glm::vec3 GetPosition();

		//Mutators
        void SetMovementSpeed(float speed);

		void SetPosition(glm::vec3 pos);
        void SetPosition(float x, float y, float z);

		void SetLookDirection(glm::vec3 look_direction);
        void SetLookDirection(float x, float y, float z);

        void SetUpDirection(glm::vec3 up_direction);
        void SetUpDirection(float x, float y, float z);

		void SetFOV(float fov);

		void SetZNear(float z_near);
		void SetZFar(float z_far);

        void NotifyScreenResize(int width, int height);

        void Update(double dt);

		virtual ~Camera();

	private:
		//Perspective variables.
		glm::mat4 m_Perspective;

        //Units: m / s
        float m_Speed;

        //Units: deg / s
        float m_RotSpeed;

        float m_ZoomFactor;

		float m_fov;
		float m_Aspect;
		float m_zNear;
		float m_zFar;

        glm::vec3 m_Position;
		glm::vec3 m_LookDirection;
		glm::vec3 m_up;

        //The initial values for perspective, so that resetting is always consistant.
        glm::vec3 m_StartingPos;
        glm::vec3 m_StartingLookDir;
        glm::vec3 m_StartingUp;

        void UpdatePerspective();

        //Reset the camera's position and orientation to it's origional values.
        void ResetPositionAndRotation();
};

#endif //MY_CAMERA_H
