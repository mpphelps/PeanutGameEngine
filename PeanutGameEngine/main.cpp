#include "Source/Graphics/window.h"
#include "Source/Graphics/shader.h"
#include "Source/Math/maths.h"
#include "Source/Utils/stb_image.h"
#include "Source/Graphics/texture.h"

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

	Window window("Peanut!", SCR_WIDTH, SCR_HEIGHT);
	Shader shader("Source/Shaders/basicClip.vert", "Source/Shaders/basicClip.frag");
	Texture texture1("Source/Textures/container.jpg", false);
	Texture texture2("Source/Textures/awesomeface.png", true);

	//float vertices[] = {
 //       // positions          // texture coords
 //        0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
 //        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
 //       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
 //       -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left 
 //   };

	glEnable(GL_DEPTH_TEST);

	constexpr float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
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

	// It is advised to first do scaling operations, then rotations and lastly translations 
	// when combining matrices otherwise they may (negatively) affect each other.

	/*mat4 trans1 = mat4::translation(vec3(0.5f, 0.5f, 0.0f));
	mat4 rot1 = mat4::rotation(180.0f, vec3(0.0f, 0.0f, 1.0f));
	mat4 scale1 = mat4::scale(vec3(0.5f, 0.5f, 0.5f));
	mat4 transform1 = rot1 * scale1;*/

	// create transformations
	/*glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	std::cout << vec.x << vec.y << vec.z << std::endl;*/

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the vertex array object first, then bind and set the vertex buffers, and then configure the vertex attributes.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean, normalized, GLsizei stride, const void *pointer);
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
		window.clear();

		texture1.bind(GL_TEXTURE0);
		texture2.bind(GL_TEXTURE1);
		
		// ****** first transformation ******
		glm::mat4 view1 = glm::mat4(1.0f);
		glm::mat4 projection1 = glm::mat4(1.0f);
		view1 = translate(view1, glm::vec3(0, 0, -5.0f));
		projection1 = glm::perspective(glm::radians(45.0f), static_cast<float>((SCR_WIDTH / SCR_HEIGHT)), 0.1f, 100.0f);

		// set shader uniform
		shader.setUniformMat4("view", view1);
		shader.setUniformMat4("projection", projection1);

		//render boxes
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model1 = glm::mat4(1.0f);
			model1 = translate(model1, cubePositions[i]);
			float angle = 20.0f * (i + 1) * (float)glfwGetTime();
			model1 = rotate(model1, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			// set shader uniform
			shader.setUniformMat4("model", model1);

			// draw contain
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ****** second transformation using my own stuff ******
		//mat4 model2 = mat4::identity();
		//mat4 view2 = mat4::identity();
		//mat4 projection2 = mat4::identity();
		//model2 = mat4::rotation(toRadians(-55.0f), vec3(1.0f, 0.0f, 0.0f));
		//view2 = mat4::translation(vec3(0.5f, -0.5f, -3.0f));
		//projection2 = mat4::perspective(toRadians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		//
		//// set shader uniform
		//shader.setUniformMat4("model", model2);
		//shader.setUniformMat4("view", view2);
		//shader.setUniformMat4("projection", projection2);
		////draw contain
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
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
