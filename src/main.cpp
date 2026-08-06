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

void _process_scroll(GLFWwindow* window, double x, double y) {
	
	
	vec3<float>	*ptr;
	
	ptr = static_cast<vec3<float> *>(glfwGetWindowUserPointer(window));
	ptr->z += (static_cast<float>(y) / 10.0f);
	
	(void)x;
}

/*
*	The process function responsible of reacting to user inputs.
*
*	Process function means it is called every frame.
*/
void _process_inputs(
	GLFWwindow* window, vec3<float> &translation, vec3<float> &rotation) {

	// static vec3<float>	translation;
	// static vec3<float>	rotation;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return ;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		translation.y += 0.1f;
	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		translation.y -= 0.1f;
	
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		translation.x -= 0.1f;
	
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		translation.x += 0.1f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		rotation.x += 0.1f;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		rotation.x -= 0.1f;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		rotation.z -= 0.1f;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		rotation.z += 0.1f;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		rotation.y -= 0.1f;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		rotation.y += 0.1f;
	
	// std::cout << translation << " | " << rotation << std::endl;
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
	glfwSetScrollCallback(*window_ptr, _process_scroll);
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
	// Shader	shader("src/SHADERS/shader.vert",
	// 				 "src/SHADERS/shader.frag");
	// shader.use();

	Shader	texture_shader("src/SHADERS/shader_texture.vert",
								"src/SHADERS/shader_texture.frag");
	texture_shader.use();

	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	Mesh mesh(argv[1]);
	Texture friends("resources/textures/test_picture.tga", true);
	Texture skull("resources/mesh/skull/Skull.tga", true);


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

		mat4x4 scale_matrix;
		mat4x4 translation_matrix; 
		mat4x4 rotation_matrix;

		vec3<float> translation;
		vec3<float>	rotation;	

		glfwSetWindowUserPointer(window, static_cast<void *>(&translation));

	while (!glfwWindowShouldClose(window)) {
		
		_process_inputs(window, translation, rotation);
		_process_render(window);

		translation_matrix = MAT4X4_TRANSLATION(translation);
		scale_matrix = MAT4X4_UNIFORM_SCALE(1);
		rotation_matrix = MAT4X4_ROTATION_X(rotation.x);

		skull.bind(0);
		texture_shader.setUniform<int>("tex", 0);
		texture_shader.setUniform<float[16]>("translate", translation_matrix.m);
		texture_shader.setUniform<float[16]>("scale", scale_matrix.m);
		texture_shader.setUniform<float[16]>("rotate", rotation_matrix.m);
		texture_shader.setUniform<float[16]>("projection", projection.m);


		// shader.setUniform<float[16]>("translate", translation_matrix.m);
		// shader.setUniform<float[16]>("scale", scale_matrix.m);
		// shader.setUniform<float[16]>("rotate", rotation_matrix.m);
		// shader.setUniform<float[16]>("projection", projection.m);

		mesh.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

