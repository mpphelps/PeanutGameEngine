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
#include "Source/Utils/log.h"



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

	Log log("C:\\temp\\PeanutEngineLog.txt");
	log.SetLogLevel(Info);

	// create and initialize glfw window
	// -----------------------------
	Window window("Peanut!", SCR_WIDTH, SCR_HEIGHT);
	log.Write("Created window object.", Info);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lightingShader("Source/Shaders/lightingShader.vert", "Source/Shaders/lightingShader.frag");
	Shader lightSourceShader("Source/Shaders/lightSourceShader.vert", "Source/Shaders/lightSourceShader.frag");
	Texture boxTexture("Source/Textures/container2.png", false);
	Texture specularMap("Source/Textures/container2_specular.png", true);
	log.Write("Created shader and texture objects.", Info);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	log.Write("Vertices for cube defined.", Info);
	// positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	log.Write("Cube positions defined.", Info);
	// define lighting variables
	// -------------------------
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	log.Write("Generated vertex arrays and buffers for main cube.", Info);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	log.Write("Buffer arrays binded for main cube.", Info);

	glBindVertexArray(cubeVAO);
	log.Write("Vertex arrays binded for main cube.", Info);
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	log.Write("Position vertices location defined for main cube.", Info);
	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	log.Write("Normal vertices location defined for main cube.", Info);
	// Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	log.Write("Texture vertices location defined for main cube.", Info);


	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	log.Write("Generated vertex arrays and buffers for light cube.", Info);
	glBindVertexArray(lightCubeVAO);
	log.Write("Vertex arrays binded for light cube.", Info);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);  not sure this is needed?
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	log.Write("Position vertices location defined for light cube.", Info);
	
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!window.closed()) {

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		window.cameraUpdate();
		window.calculateFramerate();
		window.clear();
		
		lightingShader.use();
		lightingShader.setUniformMat3f("light.position", window.camera.GetPos());
		lightingShader.setUniformMat3f("light.direction", window.camera.GetFront());
		lightingShader.setUniformMat1f("light.cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.setUniformMat1f("light.outerCutOff", glm::cos(glm::radians(17.5f)));
		lightingShader.setUniformMat3f("viewPos", window.camera.GetPos());

		lightingShader.setUniformMat3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        lightingShader.setUniformMat3f("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        lightingShader.setUniformMat3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		lightingShader.setUniformMat1f("light.constant", 1.0f);
		lightingShader.setUniformMat1f("light.linear", 0.09f);
		lightingShader.setUniformMat1f("light.quadratic", 0.032f);

		lightingShader.setUniformMat1f("material.shininess", 32.0f);		
		lightingShader.setUniformMat1i("material.diffuse", 0);
		lightingShader.setUniformMat1i("material.specular", 1);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(window.camera.Getfov()), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
		glm::mat4 view = window.camera.View();
		lightingShader.setUniformMat4("projection", projection);
		lightingShader.setUniformMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setUniformMat4("model", model);
		
		// bind diffuse map
		boxTexture.bind(GL_TEXTURE0);
		specularMap.bind(GL_TEXTURE1);

		//render cube
		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader.setUniformMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// draw the lamp object
		//lightSourceShader.use();
		//lightSourceShader.setUniformMat4("projection", projection);
		//lightSourceShader.setUniformMat4("view", view);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f));
		//lightSourceShader.setUniformMat4("model", model);
		////lightPos.x = sin(glfwGetTime()) * 2.0f;
		////lightPos.y = cos(glfwGetTime()) * 2.0f;
		////lightPos.z = sin(glfwGetTime()) * 2.0f;
		////render cube
		//glBindVertexArray(lightCubeVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		
		window.update();

	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);
	log.Write("Buffers and vertex arrays deleted.", Info);
	lightingShader.disable();
	lightingShader.~Shader();
	lightSourceShader.disable();
	lightSourceShader.~Shader();
	boxTexture.~Texture();
	specularMap.~Texture();
	log.Write("Shaders and Textures deleted.", Info);
	glfwTerminate();
	log.Write("Glfw terminated.", Info);

	return 0;
}
