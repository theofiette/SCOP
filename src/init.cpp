#include "scop.hpp"

GLFWwindow* instantiate_window()
{
	GLFWwindow* window = NULL;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "SCOP", NULL, NULL);
	if (window == NULL)
		clean_exit(true, 2);

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		clean_exit(true, 3); 

	return (window);
}

void init(int argc, GLFWwindow** window_ptr, registre *registrePtr) {

	if (argc != 2 && argc != 3)
	{
		std::cerr << "usage : [programme] [.obj file path] (.tga file path)" << std::endl;
		clean_exit(false, 0);
	}

	if (!glfwInit())
		clean_exit(false, 1); 
	*window_ptr = instantiate_window();

	glfwSetFramebufferSizeCallback(*window_ptr, _onWindowResize);
	glfwSetScrollCallback(*window_ptr, _onScroll);

	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	// glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	registrePtr->textureCoef = 1.0f;
	glfwSetWindowUserPointer(*window_ptr, static_cast<void *>(registrePtr));
}