#include "camera.h"

#define LOG(x) std::cout << x << std::endl;

namespace peanut {
	namespace graphics {
		Camera::Camera() {
			cameraFrameSpeed = 1.0f;
			cameraSpeed = m_defaultCameraSpeed;
		}

		Camera::Camera(glm::vec3 position) : Camera()
		{
			cameraPos = position;
			//cameraSpeed = m_defaultCameraSpeed;
		}

		Camera::~Camera()
		{

		}

		void Camera::ProcessKey(int key)
		{
			//std::cout << "Processing input: " << key << std::endl;
			switch (key)
			{
			case GLFW_KEY_W:
				//std::cout << "W Key Pressed" << std::endl;
				cameraPos += cameraFrameSpeed * cameraFront;
				break;
			case GLFW_KEY_S:
				//std::cout << "S Key Pressed" << std::endl;
				cameraPos -= cameraFrameSpeed * cameraFront;
				break;
			case GLFW_KEY_A:
				//std::cout << "A Key Pressed" << std::endl;
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraFrameSpeed;
				break;
			case GLFW_KEY_D:
				//std::cout << "D Key Pressed" << std::endl;
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraFrameSpeed;
				break;
			}
		}

		void Camera::ProcessMouse(double xpos, double ypos)
		{
			if (m_firstMouseInput) {
				m_lastX = xpos;
				m_lastY = ypos;
				m_firstMouseInput = false;
			}

			float xoffset = xpos - m_lastX;
			float yoffset = m_lastY - ypos; //reversed since y-coodinates ranged from bottom to top
			m_lastX = xpos;
			m_lastY = ypos;

			xoffset *= m_mouseSensitivity;
			yoffset *= m_mouseSensitivity;

			m_yaw += xoffset;
			m_pitch += yoffset;

			if (m_pitch > m_maxPitch) m_pitch = m_maxPitch;
			if (m_pitch < m_minPitch) m_pitch = m_minPitch;

			glm::vec3 direction;
			direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
			direction.y = sin(glm::radians(m_pitch));
			direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

			cameraFront = glm::normalize(direction);
		}

		void Camera::ProcessScroll(double xoffset, double yoffset)
		{
			m_fov -= (float)yoffset;
			if (m_fov < m_minFov) m_fov = m_minFov;
			if (m_fov > m_maxFov) m_fov = m_maxFov;
		}

		float Camera::Getfov() {
			return m_fov;
		}

		glm::vec3 Camera::GetPos() {
			return cameraPos;
		}

		glm::vec3 Camera::GetFront() {
			return cameraFront;
		}

		glm::mat4 Camera::View()
		{
			return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		}
	}
}
