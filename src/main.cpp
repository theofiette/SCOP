#include <scop.hpp>

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <string.h>

void _on_window_resize(GLFWwindow* window, int width, int height) {

	(void)window;
	glViewport(0, 0, width, height);
	std::cout << "Resizing window" << std::endl;
}

/*
*	The process function responsible of reacting to user inputs.
*
*	Process function means it is called every frame.
*/
void _process_inputs(GLFWwindow* window) {

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*
*	The process function responsible of rendering.
*
*	Process function means it is called every frame.
*/
void _process_render(GLFWwindow* window) {

	(void)window;
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

}

GLFWwindow* instanciate_window()
{
	GLFWwindow* window = NULL;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 800, "./SCOP", NULL, NULL);
	if (window == NULL)
		clean_exit(true, 1);

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		clean_exit(true, 1); 

	return (window);
}

void init(GLFWwindow** window_ptr) {

	if (!glfwInit())
		clean_exit(false, 1); 
	*window_ptr = instanciate_window();

	glfwSetFramebufferSizeCallback(*window_ptr, _on_window_resize);
}

int main() {

	GLFWwindow* window = NULL;

	init(&window);


	// float vertices[] = {
	// 	-0.5f,	-0.5f,	0.0f,	/*color*/	1.0f,	0.0f,	0.0f,
	// 	0.5f,	-0.5f,	0.0f,				0.0f,	1.0f,	0.0f,
	// 	0.0f,	0.5f,	0.0f,				0.0f,	0.0f,	1.0f
	// };

	// float rect_vertices[] = {
	// 	0.5f,	0.5f,	0.0f,	/*color*/	1.0f,	0.0f,	0.0f,	/*textcoord*/	1.0f, 1.0f,
	// 	0.5f,	-0.5f,	0.0f,				0.0f,	1.0f,	0.0f,					1.0f, 0.0f, 
	// 	-0.5f,	-0.5f,	0.0f,				0.0f,	0.0f,	1.0f,					0.0f, 0.0f,
	// 	-0.5f,	0.5f,	0.0f,				1.0f,	1.0f,	0.0f,					0.0f, 1.0f
	// };

	// unsigned int rect_indices[] = {
	// 	0, 1, 3,
	// 	1, 2, 3
	// };

	// float text_coord[] = {
	// 	0.0f,	0.0f,
	// 	1.0f,	0.0f,
	// 	0.5f,	1.0f
	// };
	
	// Creating the vertex shader

	Shader	shader("src/SHADERS/shader.vert",
					 "src/SHADERS/shader.frag");
	
	// shader.setUniform<float>("vertexColor", 0.5f);
	shader.use();

	///////

	// // Creating a VAO (Vertex Array Object) to create a rendering profile
	// unsigned int VAO_triangle;
	// glGenVertexArrays(1, &VAO_triangle);

	// // Bind Vertex Array Object
	// glBindVertexArray(VAO_triangle);

	// // Creating a vertex buffer object to store the vertices in the GPU memory
	// unsigned int VBO_triangle;
	// glGenBuffers(1, &VBO_triangle); // creating buffer ID
	// glBindBuffer(GL_ARRAY_BUFFER, VBO_triangle);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy vertices data in the buffer

	// // Tell OpenGL how to interpret the vertex data (for the vertex shader)
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);
	
	// ---



	// Creating another VAO for this mesh

	// unsigned int VAO_rectangle;
	// glGenVertexArrays(1, &VAO_rectangle);
	
	// glBindVertexArray(VAO_rectangle);

	// // Creating another VBO to use with an EBO
	// unsigned int VBO_rectangle;
	// glGenBuffers(1, &VBO_rectangle);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO_rectangle);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(rect_vertices), rect_vertices, GL_STATIC_DRAW); // copy vertices data in the buffer

	// // Creating an Element Buffer Object to use indices
	// unsigned int EBO;
	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect_indices), rect_indices, GL_STATIC_DRAW);

	// // Tell OpenGL how to interpret the vertex data (for the vertex shader)
	// // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);
	// glEnableVertexAttribArray(2);


	// --- Texturing the triangle

		// Global texture settings


	// Mesh rectangle("mesh/rectangle.obj");
	// Mesh triangle("mesh/triangle.obj");

	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	
	// Mesh rect("mesh/1f_rectangle.obj");
	// Mesh rect("mesh/rectangle.obj");
	// Mesh textureRect("mesh/texture_rect.obj");
	// Mesh logo("resources/42.obj");
	// Mesh pyramid("mesh/pyramid.obj");
	Mesh teapot("resources/teapot.obj");
	
	Texture mire("textures/mire.tga", true);
	Texture friends("textures/test_picture.tga", true);

	//TODO : this block should be part of the texture class, but how ??.....
	// texture repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_CULL_FACE);

	float z_offset = 0;

	while (!glfwWindowShouldClose(window)) {
		
		_process_inputs(window);
		_process_render(window);

		// test
		// float timeValue = glfwGetTime();
		// float turnValue = (sin(timeValue) / 2.0f);
		// shader.setUniform<float>("turnValue", turnValue);

		// // To draw the triangle
		// glBindVertexArray(VAO_triangle);
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		// To draw the rectangle
		// mire.bind(0);

		shader.setUniform<float>("offset", /*0 * sinf(z_offset)*/1);
		shader.setUniform<float>("tanhalffov", tan(45 * 360 / (M_PI * 2)));
		z_offset += 0.02;

		friends.bind(1);
		// shader.setUniform<int>("tex", 1);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		teapot.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

