#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace peanut {

	class FileUtils {
	public:
		static std::string readShaderFile(const char* filepath) {

			std::string code;
			std::ifstream shaderFile;

			// ensure ifstream objects can throw exceptions:
			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			try {
				// open file
				shaderFile.open(filepath);
				std::stringstream shaderStream;
				// read file's buffer contents into stream
				shaderStream << shaderFile.rdbuf();
				// close file handler
				shaderFile.close();
				// convert stream into string
				code = shaderStream.str();
			}
			catch (std::ifstream::failure e) {
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
				std::cout << e.what() << std::endl;
				throw;
			}

			return code.c_str();
		}
	};
	

}