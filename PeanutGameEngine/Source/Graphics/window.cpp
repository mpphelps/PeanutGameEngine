#include "Window.h"

#define LOG(x) std::cout << x << std::endl;

namespace peanut{
	namespace graphics {

		void window_resize(GLFWwindow* window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

		Window::Window(const char* title, int width, int height)
			{
			m_Title = title;
			m_Width = width;
			m_Height = height;
			if (!init()) {
				glfwTerminate();
			}
			for (int i = 0; i < MAX_KEYS; i++) {
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_MouseButtons[i] = false;
			}			
		}

		Window::~Window() {
			glfwTerminate();
		}

		bool Window::init() {

			if (!glfwInit()) {
				LOG("Failed to initialize GLFW");
				return false;
			}


			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window) {
				glfwTerminate();
				LOG("Failed to create GLFW Window");
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			glfwSetScrollCallback(m_Window, scroll_callback);

			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (glewInit() != GLEW_OK) {
				LOG("Could not initalize GLEW!");
				return false;
			}

			// configure global opengl state
			// -----------------------------
			glEnable(GL_DEPTH_TEST);

			std::cout << "OpenGL" << glGetString(GL_VERSION) << std::endl;

			return true;
		}

		bool Window::isKeyPressed(unsigned int keycode) const {
			if (keycode >= MAX_KEYS)
				return false;
			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const {
			if (button >= MAX_BUTTONS)
				return false;
			return m_MouseButtons[button];
		}

		void Window::getMousePosition(double& x, double& y) const {
			x = mx;
			y = my;
		}

		void Window::cameraUpdate() {
			float currentFrame = static_cast<float>(glfwGetTime());
			m_DeltaTime = currentFrame - m_LastFrame;
			m_LastFrame = currentFrame;

			camera.cameraFrameSpeed = m_DeltaTime * camera.cameraSpeed;
			if (isKeyPressed(GLFW_KEY_W)) camera.ProcessKey(GLFW_KEY_W);
			if (isKeyPressed(GLFW_KEY_S)) camera.ProcessKey(GLFW_KEY_S);
			if (isKeyPressed(GLFW_KEY_A)) camera.ProcessKey(GLFW_KEY_A);
			if (isKeyPressed(GLFW_KEY_D)) camera.ProcessKey(GLFW_KEY_D);
		}

		void Window::calculateFramerate() {
			m_DeltaTimes[m_DeltaTimesIndex] = m_DeltaTime;
			m_DeltaTimesIndex++;
			int maxSamples = sizeof(m_DeltaTimes) / sizeof(float);
			if (m_DeltaTimesIndex == maxSamples) {
				m_DeltaTimesIndex = 0;
				float average = 0.0f;
				for (float time : m_DeltaTimes) {
					average += time;
				}
				average = average / maxSamples;
				std::cout << "fps: " << (1 / average) << std::endl;
			}
		}


		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
			//glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_resize(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->setWidth(width);
			win->setWidth(height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
			//std::cout << "Pressed key: " << key << " Action: " << action << std::endl;
		}
		
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->camera.ProcessScroll(xoffset, yoffset);
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;		
			win->camera.ProcessMouse(xpos, ypos);

		}
	}
}
