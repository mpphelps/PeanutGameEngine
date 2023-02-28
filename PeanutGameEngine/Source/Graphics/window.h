#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "camera.h"

namespace peanut{
	namespace graphics {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

		class Window {

		private: 
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;

			// Key and mouse variables
			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			double mx, my;

			// Frame variables
			float m_DeltaTime = 0.0f;
			float m_LastFrame = 0.0f;
			float m_DeltaTimes[100];
			int m_DeltaTimesIndex = 0;
		public:
			Camera camera;

		public:
			Window(const char* title, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

			inline int getWidth() const { return m_Width;  }
			inline int getHeight() const { return m_Height; }
			inline void setWidth(int width) { m_Width = width; }
			inline void setHeight(int height)  { m_Height = height; }

			void cameraUpdate();
			void calculateFramerate();

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;

		private:
			bool init();
			friend static void window_resize(GLFWwindow* window, int width, int height);
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};

	}
}
