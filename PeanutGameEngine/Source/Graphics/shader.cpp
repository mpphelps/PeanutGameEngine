#include "shader.h"
#include "../glm/gtc/type_ptr.hpp"

namespace peanut {
	namespace graphics {

		Shader::Shader(const char* vertPath, const char* fragPath) 
			: m_Vertpath(vertPath), m_Fragpath(fragPath) 
		{
			m_ShaderID = load();
		}

		Shader::~Shader() {
			glDeleteProgram(m_ShaderID);
		}

		void Shader::use() const {
			glUseProgram(m_ShaderID);
		}

		void Shader::disable() const {
			glUseProgram(0);
		}

		GLuint Shader::load() {
			GLuint vertexShader = compileShader(m_Vertpath, GL_VERTEX_SHADER);
			GLuint fragmentShader = compileShader(m_Fragpath, GL_FRAGMENT_SHADER);
			GLuint shaderProgram = linkShaderProgram(vertexShader, fragmentShader);
			return shaderProgram;
		}

		GLuint Shader::compileShader(const char* shaderPath, GLenum type) {
			GLuint shader = glCreateShader(type);
			std::string shaderSourceString = FileUtils::readShaderFile(shaderPath);
			const char* shaderSource = shaderSourceString.c_str();
			// Compile vertex shaders
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);

			// Check for vertex shader compile problems
			GLint result;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(shader, length, &length, &error[0]);
				std::cout << "Failed to compile " << shaderPath << " shader" << std::endl << &error[0] << std::endl;
				glDeleteShader(shader);
				return 0;
			}
			return shader;
		}

		GLuint Shader::linkShaderProgram(GLuint vertex, GLuint fragment) {
			GLuint program = glCreateProgram();
			// Link shaders
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);

			// Check for sahder program linking errors
			GLint result;
			glGetProgramiv(program, GL_LINK_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetProgramInfoLog(program, length, NULL, &error[0]);
				std::cout << "Failed to compile fragment shader" << std::endl << &error[0] << std::endl;
				glDeleteShader(program);
				return 0;
			}
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

        GLuint Shader::GetShaderID()
        {
			return m_ShaderID;
        }

        GLint Shader::getUniformLocation(const GLchar* name) {
			return glGetUniformLocation(m_ShaderID, name);
		}

		void Shader::setUniformMat1f(const GLchar* name, float value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniformMat1i(const GLchar* name, int value) {
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniformMat2f(const GLchar* name, const glm::vec2& vector) {
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniformMat3f(const GLchar* name, const glm::vec3& vector) {
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniformMat4f(const GLchar* name, const glm::vec4& vector) {
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
		}

	}
}