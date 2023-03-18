#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

namespace peanut {
	namespace graphics {

		class Camera {

		public:
			float cameraSpeed;
			float cameraFrameSpeed;

		private:
			glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
			glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

			// Camera Speed Variables
			float m_mouseSensitivity = 0.05f;
			float m_defaultCameraSpeed = 10.0f;
			// Camera Zoom Variables
			float m_fov = 45.0f;
			float m_minFov = 1.0f;
			float m_maxFov = 45.0f;
			// Camera Direction Variables
			float m_lastX = 0.0f;
			float m_lastY = 0.0f;
			float m_yaw = -90.0f;
			float m_pitch = 0.0f;
			bool  m_firstMouseInput = true;
			float m_maxPitch = 89.0;
			float m_minPitch = -89.0;


		public:
			Camera();
			Camera(glm::vec3 position);
			~Camera();
			void ProcessKey(int key);
			void ProcessMouse(double xpos, double ypos);
			void ProcessScroll(double xoffset, double yoffset);
			float Getfov();
			glm::vec3 GetPos();
			glm::mat4 View();
		};
	}
}