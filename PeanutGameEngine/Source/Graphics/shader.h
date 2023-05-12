#pragma once
#include <GL/glew.h>
#include "../glm/glm.hpp"

#include "../Utils/fileutils.h"

#include <vector>
#include <iostream>

namespace peanut {
	namespace graphics {

		class Shader {
		private:
			GLuint m_ShaderID;
			const char* m_Vertpath;
			const char* m_Fragpath;
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void setUniformMat1f(const GLchar* name, float value);
			void setUniformMat1i(const GLchar* name, int value);
			void setUniformMat2f(const GLchar* name, const glm::vec2& vector);
			void setUniformMat3f(const GLchar* name, const glm::vec3& vector);
			void setUniformMat4f(const GLchar* name, const glm::vec4& vector);
			void setUniformMat4(const GLchar* name, const glm::mat4& matrix);

			void use() const;
			void disable() const;

			GLuint GetShaderID();

		private:
			GLint getUniformLocation(const GLchar* name);
			GLuint load();
			GLuint compileShader(const char* shaderPath, GLenum type);
			GLuint linkShaderProgram(GLuint vertex, GLuint fragment);
			
			
		};

	}
}