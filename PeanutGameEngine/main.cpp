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

	// create and initialize glfw window
	// -----------------------------
	Window window("Peanut!", SCR_WIDTH, SCR_HEIGHT);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lightingShader("Source/Shaders/lightingShader.vert", "Source/Shaders/lightingShader.frag");
	Shader lightSourceShader("Source/Shaders/lightSourceShader.vert", "Source/Shaders/lightSourceShader.frag");
	//Texture texture1("Source/Textures/container.jpg", false);
	//Texture texture2("Source/Textures/awesomeface.png", true);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	// define lighting variables
	// -------------------------
	glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
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
		lightingShader.setUniformMat3f("lightPos", lightPos);
		lightingShader.setUniformMat3f("viewPos", window.camera.GetPos());
		lightingShader.setUniformMat3f("material.ambient",  glm::vec3(0.0f, 0.1f, 0.06f));
		lightingShader.setUniformMat3f("material.diffuse",  glm::vec3(0.0f, 0.50980392f, 0.50980392f));
		lightingShader.setUniformMat3f("material.specular", glm::vec3(0.50196078f, 0.50196078f, 0.50196078f));
		lightingShader.setUniformMat1f("material.shininess", 32.0f);
		glm::vec3 lightColor;
		lightColor.r = sin(glfwGetTime() * 2.0f);
		lightColor.g = sin(glfwGetTime() * 0.7f);
		lightColor.b = sin(glfwGetTime() * 1.3f);
		glm::vec3 ambientColor = lightColor * glm::vec3(0.2f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		lightingShader.setUniformMat3f("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		lightingShader.setUniformMat3f("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		lightingShader.setUniformMat3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

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
		model = glm::scale(model, glm::vec3(0.2f));
		lightSourceShader.setUniformMat4("model", model);
		lightPos.x = sin(glfwGetTime()) * 2.0f;
		lightPos.y = cos(glfwGetTime()) * 2.0f;
		lightPos.z = sin(glfwGetTime()) * 2.0f;
		//render cube
		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		window.update();

	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
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
