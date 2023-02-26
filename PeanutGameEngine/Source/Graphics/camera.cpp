#include "camera.h"

#define LOG(x) std::cout << x << std::endl;

namespace peanut {
	namespace graphics {
		Camera::Camera() {
			cameraSpeed = 0.1f;
		}

		Camera::Camera(glm::vec3 position)
		{
			cameraPos = position;
			cameraSpeed = 0.1f;
		}

		Camera::~Camera()
		{

		}

		void Camera::ProcessInput(int key)
		{
			//std::cout << "Processing input: " << key << std::endl;
			switch (key)
			{
			case GLFW_KEY_W:
				//std::cout << "W Key Pressed" << std::endl;
				cameraPos += cameraSpeed * cameraFront;
				break;
			case GLFW_KEY_S:
				//std::cout << "S Key Pressed" << std::endl;
				cameraPos -= cameraSpeed * cameraFront;
				break;
			case GLFW_KEY_A:
				//std::cout << "A Key Pressed" << std::endl;
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				break;
			case GLFW_KEY_D:
				//std::cout << "D Key Pressed" << std::endl;
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				break;
			}
		}

		void Camera::ProcessMouse(double xpos, double ypos)
		{
			if (firstMouse) {
				m_lastX = xpos;
				m_lastY = ypos;
				firstMouse = false;
				return;
			}
			float xoffset = xpos - m_lastX;
			float yoffset = m_lastY - ypos; //reversed since y-coodinates ranged from bottom to top
			m_lastX = xpos;
			m_lastY = ypos;

			const float sensitivity = 0.1f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			m_yaw += xoffset;
			m_pitch += yoffset;

			if (m_pitch > 89.0f) m_pitch = 89.0f;
			if (m_pitch < -89.0f) m_pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
			direction.y = sin(glm::radians(m_pitch));
			direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

			cameraFront = glm::normalize(direction);
		}

		void Camera::ProcessScroll(double xoffset, double yoffset)
		{
			fov -= (float)yoffset;
			if (fov < 1.0f) fov = 1.0f;
			if (fov > 45.0f) fov = 45.0f;
		}

		glm::mat4 Camera::View()
		{
			return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		}
	}
}
