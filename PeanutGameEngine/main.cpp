#include "Source/Graphics/window.h"
#include "Source/Graphics/shader.h"
#include "Source/Math/maths.h"

#define LOG(x) std::cout << x << std::endl;

int main()
{
	using namespace peanut;
	using namespace graphics;
	using namespace maths;

	Window window("Peanut!", 960, 540);

	Shader shader("Source/Shaders/basic.vert", "Source/Shaders/basic.frag");

	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 //-0.5f,  0.5f, 0.0f,

		 // 0.5f, -0.5f, 0.0f,
		   -0.5f, -0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f,
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};


	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);*/

	/*mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("Source/Shaders/basic.vert", "Source/Shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4,3,0)));

	shader.setUniformMat2f("light_pos", vec2(4.0f, 1.5f));
	shader.setUniformMat4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));*/

	// uncomment this call to draw in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!window.closed()) {
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		window.clear();

		shader.enable();

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		/*glDrawArrays(GL_TRIANGLES, 0, 6);*/
		window.update();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	shader.disable();
	shader.~Shader();
	return 0;
}