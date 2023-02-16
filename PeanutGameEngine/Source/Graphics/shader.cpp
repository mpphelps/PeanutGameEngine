#include "shader.h"

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

		void Shader::enable() const {
			glUseProgram(m_ShaderID);
		}

		void Shader::disable() const {
			glUseProgram(0);
		}

		GLuint Shader::load() {
			GLuint vertexShader = compileVertexShader();
			GLuint fragmentShader = compileFragmentShader();
			GLuint shaderProgram = linkShaderProgram(vertexShader, fragmentShader);
			return shaderProgram;
		}

		GLuint Shader::compileVertexShader() {
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			std::string vertSourceString = FileUtils::read_file(m_Vertpath);
			const char* vertSource = vertSourceString.c_str();
			// Compile vertex shaders
			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);

			// Check for vertex shader compile problems
			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader" << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}
			return vertex;
		}

		GLuint Shader::compileFragmentShader() {
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
			std::string fragSourceString = FileUtils::read_file(m_Fragpath);
			const char* fragSource = fragSourceString.c_str();

			// Compile fragment shaders
			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);

			// Check for fragment shader compile problems
			GLint result;
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader" << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}
			return fragment;
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


		GLint Shader::getUniformLocation(const GLchar* name) {
			return glGetUniformLocation(m_ShaderID, name);
		}

		void Shader::setUniformMat1f(const GLchar* name, float value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniformMat1i(const GLchar* name, int value) {
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniformMat2f(const GLchar* name, const maths::vec2& vector) {
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniformMat3f(const GLchar* name, const maths::vec3& vector) {
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniformMat4f(const GLchar* name, const maths::vec4& vector) {
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

	}
}