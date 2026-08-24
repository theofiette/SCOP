#include "scop.hpp"

int clean_exit(bool should_glfwTerminate, int exit_code)
{
	if (should_glfwTerminate)
		glfwTerminate();
	std::exit(exit_code);
}