#include "Source/Graphics/window.h"
#include "Source/Graphics/camera.h"
#include "Source/Graphics/shader.h"
#include "Source/Math/maths.h"
#include "Source/Utils/stb_image.h"
#include "Source/Graphics/texture.h"
#include "Source/Objects/cubes.h"

#include "Source/glm/glm.hpp"
#include "Source/glm/gtc/matrix_transform.hpp"
#include "Source/glm/gtc/type_ptr.hpp"



#define SCR_WIDTH 800
#define SCR_HEIGHT 600
#define LOG(x) std::cout << x << std::endl;

// GLSL language integration
//https://marketplace.visualstudio.com/items?itemName=DanielScherzer.GLSL

int main()
{
	using namespace peanut;
	using namespace graphics;
	using namespace maths;
	using namespace objects;

	glEnable(GL_DEPTH_TEST);

	Window window("Peanut!", SCR_WIDTH, SCR_HEIGHT);
	Shader lightingShader("Source/Shaders/lightingShader.vert", "Source/Shaders/lightingShader.frag");
	Shader lightSourceShader("Source/Shaders/lightSourceShader.vert", "Source/Shaders/lightSourceShader.frag");
	//Texture texture1("Source/Textures/container.jpg", false);
	//Texture texture2("Source/Textures/awesomeface.png", true);
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};
	// lighting
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	// It is advised to first do scaling operations, then rotations and lastly translations 
	// when combining matrices otherwise they may (negatively) affect each other.

	GLuint VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// bind the vertex array object first, then bind and set the vertex buffers, and then configure the vertex attributes.
	glBindVertexArray(cubeVAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint lightSourceVAO;
	glGenVertexArrays(1, &lightSourceVAO);
	glBindVertexArray(lightSourceVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!window.closed()) {

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		window.cameraUpdate();
		window.calculateFramerate();

		window.clear();

		//texture1.bind(GL_TEXTURE0);
		//texture2.bind(GL_TEXTURE1);
		
		lightingShader.use();
		lightingShader.setUniformMat3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		lightingShader.setUniformMat3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

		// ****** view/projection/model transformation ******
		glm::mat4 projection = glm::perspective(glm::radians(window.camera.Getfov()), static_cast<float>((window.getWidth() / window.getHeight())), 0.1f, 100.0f);
		glm::mat4 view = window.camera.View();
		glm::mat4 model = glm::mat4(1.0f);
		// set shader uniform
		lightingShader.setUniformMat4("projection", projection);
		lightingShader.setUniformMat4("view", view);
		lightingShader.setUniformMat4("model", model);
		
		//render cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// draw the lamp object
		lightSourceShader.use();
		lightSourceShader.setUniformMat4("projection", projection);
		lightSourceShader.setUniformMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2));
		lightSourceShader.setUniformMat4("model", model);

		//render cube
		glBindVertexArray(lightSourceVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		window.update();

	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightSourceVAO);
	glDeleteBuffers(1, &VBO);
	lightingShader.disable();
	lightingShader.~Shader();
	lightSourceShader.disable();
	lightSourceShader.~Shader();
	//texture1.~Texture();
	//texture2.~Texture();
	glfwTerminate();
	return 0;
}
