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

		public:
			Camera();
			Camera(glm::vec3 position);
			~Camera();
			void ProcessInput(int key);
			glm::mat4 View();
		};
	}
}