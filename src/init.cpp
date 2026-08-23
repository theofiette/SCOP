#include "scop.hpp"

GLFWwindow* instanciate_window()
{
	GLFWwindow* window = NULL;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGTH, "./SCOP", NULL, NULL);
	if (window == NULL)
		clean_exit(true, 1);

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		clean_exit(true, 1); 

	return (window);
}

void init(GLFWwindow** window_ptr, registre *registrePtr) {

	if (!glfwInit())
		clean_exit(false, 1); 
	*window_ptr = instanciate_window();

	glfwSetFramebufferSizeCallback(*window_ptr, _onWindowResize);
	glfwSetScrollCallback(*window_ptr, _onScroll);

	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glfwSetWindowUserPointer(*window_ptr, static_cast<void *>(registrePtr));
}