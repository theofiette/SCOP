#include "scop.hpp"
#include "stdlib.h"

int clean_exit(bool should_glfwTerminate, int exit_code)
{
	if (should_glfwTerminate)
		glfwTerminate();
	exit(exit_code);
}