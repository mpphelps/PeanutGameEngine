#include "texture.h"

namespace peanut {
	namespace graphics {

		Texture::Texture(const char* texturepath, bool flipYaxis) {
			m_Texturepath = texturepath;

			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			// set the texture wrapping/filtering options (on the currently bound texture object)

			// coordinates outside texture ranges (3rd param in glTexParameteri)
			// GL_REPEAT : The default behavior for textures. Repeats the texture image.
			// GL_MIRRORED_REPEAT: Same as GL_REPEAT but mirrors the image with each repeat.
			// GL_CLAMP_TO_EDGE : Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
			// GL_CLAMP_TO_BORDER : Coordinates outside the range are now given a user - specified border color.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// GL_NEAREST results in pixelated pattern
			// GL_LINEAR produces a smoother pattern but blurry
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Use this if using GL_CLAMP_TO_BORDER to set border color around texture if needing more th
			/*float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);*/

			if (flipYaxis) stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
			unsigned char* data = stbi_load(m_Texturepath.c_str(), &m_Width, &m_Height, &m_nrChannels, 0);

			if (data) {
				
				if (m_Texturepath.find(".png") != std::string::npos) {
					// .png files have an alpha transparency value that openGL needs to know about
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				}
				else if (m_Texturepath.find(".jpg") != std::string::npos) {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				}
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



		void Texture::bind(GLenum texture) {
			// Texture Units can be from GL_TEXTURE0 to 15
			glActiveTexture(texture);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
		}


	}
}