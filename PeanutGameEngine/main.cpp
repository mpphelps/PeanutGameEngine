#include "Source/Graphics/window.h"
#include "Source/Graphics/camera.h"
#include "Source/Graphics/shader.h"
#include "Source/Graphics/model.h"
#include "Source/Math/maths.h"
#include "Source/Utils/stb_image.h"
#include "Source/Graphics/textureImage.h"
#include "Source/Objects/cubes.h"

#include "Source/glm/glm.hpp"
#include "Source/glm/gtc/matrix_transform.hpp"
#include "Source/glm/gtc/type_ptr.hpp"
#include "Source/Utils/log.h"

#include "../Dependencies/ASSIMP/include/assimp/scene.h"
#include <iostream>


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
	Shader ourShader("Source/Shaders/modelLoading.vert", "Source/Shaders/modelLoading.frag");
	Model ourModel("Source/Objects/SurvivalBackpack/backpack.obj");
	log.Write("Created shader and model objects.", Info);


	while (!window.closed()) {

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		window.cameraUpdate();
		window.calculateFramerate();
		window.clear();
		
		ourShader.use();
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(window.camera.Getfov()), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);
		glm::mat4 view = window.camera.View();
		ourShader.setUniformMat4("projection", projection);
		ourShader.setUniformMat4("view", view);

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		ourShader.setUniformMat4("model", model);
		ourModel.Draw(ourShader);
				
		window.update();

	}

	log.Write("Buffers and vertex arrays deleted.", Info);
	ourShader.disable();
	ourShader.~Shader();
	log.Write("Shaders and Textures deleted.", Info);
	glfwTerminate();
	log.Write("Glfw terminated.", Info);

	return 0;
}
