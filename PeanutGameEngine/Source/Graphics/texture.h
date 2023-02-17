#pragma once
#include <GL/glew.h>


namespace peanut {
	namespace graphics {

		class Texture {
		private:
			GLuint m_TextureID;
			const char* m_Texturepath;
			int m_Width, m_Height, m_nrChannels;
		public:
			Texture(const char* texturepath);
			~Texture();
			void Bind();
		};

	}
}
