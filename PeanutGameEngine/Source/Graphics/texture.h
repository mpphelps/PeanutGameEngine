#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include "../Utils/stb_image.h"

namespace peanut {
	namespace graphics {

		class Texture {
		private:
			GLuint m_TextureID;
			std::string m_Texturepath;
			int m_Width, m_Height, m_nrChannels;
		public:
			Texture(const char* texturepath, bool flipYaxis);
			~Texture();
			void bind(GLenum texture);
		};

	}
}
