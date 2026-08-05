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

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		std::cout << "UP\n" << std::endl;
	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		std::cout << "DOWN\n" << std::endl;
	
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		std::cout << "LEFT\n" << std::endl;
	
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		std::cout << "RIGHT\n" << std::endl;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		std::cout << "W\n" << std::endl;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		std::cout << "A\n" << std::endl;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		std::cout << "S\n" << std::endl;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		std::cout << "D\n" << std::endl;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		std::cout << "Q\n" << std::endl;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		std::cout << "E\n" << std::endl;
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

	Shader	texture_shader("src/SHADERS/shader_texture.vert",
								"src/SHADERS/shader_texture.frag");
	texture_shader.use();

	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	// glEnable(GL_CULL_FACE);
	// glEnable(GL_DEPTH_TEST);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	Mesh mesh(argv[1]);
	Texture friends("resources/textures/test_picture.tga", true);


	// PROJECTION MATRIX

		mat4x4 projection = MAT4X4(0);

		const float fov = 90.0f * M_PI / 180.0f;
		const float ratio = 1.0f;
		const float znear = 0.1f;
		const float zfar = 100.0f;
		projection.mat[0][0] = (1 / (ratio * tan(fov / 2)));
		projection.mat[1][1] = (1 / (tan(fov/2)));
		projection.mat[2][2] = -((zfar + znear) / (zfar - znear));
		projection.mat[2][3] = -((2 * zfar * znear) / (zfar - znear));
		projection.mat[3][2] = -1;

	// TRANSFORMATION MATRIX

		mat4x4 transformation = MAT4X4_UNIFORM_SCALE(2.2);claer

		vec3<float> translation_factor;
		translation_factor.x = 0.5;
		translation_factor.y = -0.5;
		translation_factor.z = 1;
		transformation = MAT4X4_TRANSLATION(translation_factor);

	while (!glfwWindowShouldClose(window)) {
		
		_process_inputs(window);
		_process_render(window);

		friends.bind(0);
		shader.setUniform<int>("tex", 0);
		shader.setUniform<float[16]>("projection", projection.m);
		shader.setUniform<float[16]>("transformation", transformation.m);

		mesh.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

