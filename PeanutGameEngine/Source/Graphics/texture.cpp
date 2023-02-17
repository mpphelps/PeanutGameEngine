#include "texture.h"
#include "../Utils/stb_image.h"
#include <iostream>

namespace peanut {
	namespace graphics {

		Texture::Texture(const char* texturepath) {
			m_Texturepath = texturepath;
			unsigned char* data = stbi_load("Source/Textures/container.jpg", &m_Width, &m_Height, &m_nrChannels, 0);
			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			// set the texture wrapping/filtering options (on the currently bound texture object)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else {
				std::cout << "Failed to load texture: " << m_Texturepath << std::endl;
			}
			stbi_image_free(data);
		}

		Texture::~Texture(){
			glDeleteProgram(m_TextureID);
		};

		void Texture::Bind() {
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
		}


	}
}