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

	Window window("Peanut!", SCR_WIDTH, SCR_HEIGHT);
	Shader shader("Source/Shaders/basicClip.vert", "Source/Shaders/basicClip.frag");
	Texture texture1("Source/Textures/container.jpg", false);
	Texture texture2("Source/Textures/awesomeface.png", true);
	Camera camera;
	Cubes cubes;
	cubes.AddCube(glm::vec3(0.0f, 0.0f, 0.0f));
	cubes.AddCube(glm::vec3(0.0f, 0.0f, 0.0f));
	cubes.AddCube(glm::vec3(2.0f, 5.0f, -15.0f));
	cubes.AddCube(glm::vec3(-1.5f, -2.2f, -2.5f));
	cubes.AddCube(glm::vec3(-3.8f, -2.0f, -12.3f));
	cubes.AddCube(glm::vec3(2.4f, -0.4f, -3.5f));
	cubes.AddCube(glm::vec3(-1.7f, 3.0f, -7.5f));
	cubes.AddCube(glm::vec3(1.3f, -2.0f, -2.5f));
	cubes.AddCube(glm::vec3(1.5f, 2.0f, -2.5f));
	cubes.AddCube(glm::vec3(1.5f, 0.2f, -1.5f));
	cubes.AddCube(glm::vec3(-1.3f, 1.0f, -1.5f));
	cubes.AddCube(glm::vec3(1.1f, -2.0f, -2.5f));
	cubes.AddCube(glm::vec3(3.2f, -2.0f, -2.5f));
	cubes.AddCube(glm::vec3(4.3f, -2.0f, -2.5f));
	cubes.AddCube(glm::vec3(6.4f, -2.0f, -2.5f));
	cubes.AddCube(glm::vec3(8.5f, -2.0f, -2.5f));
	cubes.AddCube(glm::vec3(10.6f, -2.0f, -2.5f));
	cubes.AddCube(glm::vec3(12.7f, -2.0f, -2.5f));
	cubes.AddCube(glm::vec3(14.3f, -2.0f, -2.5f));

	glEnable(GL_DEPTH_TEST);

	// It is advised to first do scaling operations, then rotations and lastly translations 
	// when combining matrices otherwise they may (negatively) affect each other.

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the vertex array object first, then bind and set the vertex buffers, and then configure the vertex attributes.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubes.vertices), cubes.vertices, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shader.use();
	shader.setUniformMat1i("texture1", 0);
	shader.setUniformMat1i("texture2", 1);
	shader.setUniformMat1f("mixture", 0.5f);	

	while (!window.closed()) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		window.cameraUpdate();
		window.calculateFramerate();

		window.clear();

		texture1.bind(GL_TEXTURE0);
		texture2.bind(GL_TEXTURE1);
		
		// ****** first transformation ******
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(window.camera.Getfov()), static_cast<float>((window.getWidth() / window.getHeight())), 0.1f, 100.0f);
		// ****** third transformation ******
		glm::mat4 view = window.camera.View();
		// set shader uniform
		shader.setUniformMat4("view", view);
		shader.setUniformMat4("projection", projection);

		//render boxes
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < cubes.Count(); i++)
		{
			// ****** second transformation ******
			glm::mat4 model = glm::mat4(1.0f);
			model = translate(model, cubes.GetPosition(i));
			float angle = 20.0f * (i + 1) * (float)glfwGetTime();
			model = rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			// set shader uniform
			shader.setUniformMat4("model", model);

			// draw contain
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		
		window.update();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	shader.disable();
	shader.~Shader();
	texture1.~Texture();
	texture2.~Texture();
	glfwTerminate();
	return 0;
}
