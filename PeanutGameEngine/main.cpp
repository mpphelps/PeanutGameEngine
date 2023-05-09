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

#include "../Dependencies/ASSIMP/include/assimp/scene.h"

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
	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
	log.Write("Point light positions defined.", Info);

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

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
		lightingShader.setUniformMat3f("viewPos", window.camera.GetPos());
		lightingShader.setUniformMat1f("material.shininess", 32.0f);

		/*
		   Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		   the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		   by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		   by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
		// directional light
		lightingShader.setUniformMat3f("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		lightingShader.setUniformMat3f("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		lightingShader.setUniformMat3f("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		lightingShader.setUniformMat3f("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		// point light 1
		lightingShader.setUniformMat3f("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setUniformMat3f("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		lightingShader.setUniformMat3f("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		lightingShader.setUniformMat3f("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		lightingShader.setUniformMat1f("pointLights[0].constant", 1.0f);
		lightingShader.setUniformMat1f("pointLights[0].linear", 0.09f);
		lightingShader.setUniformMat1f("pointLights[0].quadratic", 0.032f);
		// point light 2
		lightingShader.setUniformMat3f("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setUniformMat3f("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		lightingShader.setUniformMat3f("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		lightingShader.setUniformMat3f("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		lightingShader.setUniformMat1f("pointLights[1].constant", 1.0f);
		lightingShader.setUniformMat1f("pointLights[1].linear", 0.09f);
		lightingShader.setUniformMat1f("pointLights[1].quadratic", 0.032f);
		// point light 3
		lightingShader.setUniformMat3f("pointLights[2].position", pointLightPositions[2]);
		lightingShader.setUniformMat3f("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		lightingShader.setUniformMat3f("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		lightingShader.setUniformMat3f("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		lightingShader.setUniformMat1f("pointLights[2].constant", 1.0f);
		lightingShader.setUniformMat1f("pointLights[2].linear", 0.09f);
		lightingShader.setUniformMat1f("pointLights[2].quadratic", 0.032f);
		// point light 4
		lightingShader.setUniformMat3f("pointLights[3].position", pointLightPositions[3]);
		lightingShader.setUniformMat3f("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		lightingShader.setUniformMat3f("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		lightingShader.setUniformMat3f("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		lightingShader.setUniformMat1f("pointLights[3].constant", 1.0f);
		lightingShader.setUniformMat1f("pointLights[3].linear", 0.09f);
		lightingShader.setUniformMat1f("pointLights[3].quadratic", 0.032f);
		// spotLight
		lightingShader.setUniformMat3f("spotLight.position", window.camera.GetPos());
		lightingShader.setUniformMat3f("spotLight.direction", window.camera.GetFront());
		lightingShader.setUniformMat3f("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		lightingShader.setUniformMat3f("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		lightingShader.setUniformMat3f("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		lightingShader.setUniformMat1f("spotLight.constant", 1.0f);
		lightingShader.setUniformMat1f("spotLight.linear", 0.09f);
		lightingShader.setUniformMat1f("spotLight.quadratic", 0.032f);
		lightingShader.setUniformMat1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.setUniformMat1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

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
		lightSourceShader.use();
		lightSourceShader.setUniformMat4("projection", projection);
		lightSourceShader.setUniformMat4("view", view);

		// we now draw as many light bulbs as we have point lights.
		glBindVertexArray(lightCubeVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			lightSourceShader.setUniformMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
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
