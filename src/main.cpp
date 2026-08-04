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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

int main(int argc, char *argv[]) {

	if (argc != 2)
	{
		std::cerr << "usage : [programme] [.obj file path]" << std::endl;
		clean_exit(false, 1);
	}

	GLFWwindow* window = NULL;

	init(&window);
	
	// Creating the vertex shader
	Shader	shader("src/SHADERS/shader.vert",
					 "src/SHADERS/shader.frag");
	shader.use();

	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	Mesh mesh(argv[1]);
	Texture friends("resources/textures/test_picture.tga", true);

	float z_offset = 0;

	mat4x4 projection = {};
		
	const float fov = 90.0f * M_PI / 180.0f;
	const float ratio = 1.0f;
	const float znear = 0.1f;
	const float zfar = 100.0f;
	projection.mat[0][0] = (1 / (ratio * tan(fov / 2)));
	projection.mat[1][1] = (1 / (tan(fov/2)));
	projection.mat[2][2] = -((zfar + znear) / (zfar - znear));
	projection.mat[2][3] = -((2 * zfar * znear) / (zfar - znear));
	projection.mat[3][2] = -1;


	while (!glfwWindowShouldClose(window)) {
		
		_process_inputs(window);
		_process_render(window);

		shader.setUniform<float>("offset", /*0 * sinf(z_offset)*/1);
		shader.setUniform<float>("tanhalffov", tan(45 * 360 / (M_PI * 2)));
		z_offset += 0.02;

		friends.bind(0);
		shader.setUniform<int>("tex", 0);
		shader.setUniform<float[16]>("projection", projection.m);

		mesh.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

