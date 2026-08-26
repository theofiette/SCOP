#include "scop.hpp"

int clean_exit(bool should_glfwTerminate, int exit_code)
{
	std::string error_str;

	if (should_glfwTerminate)
		glfwTerminate();

	switch (exit_code)
	{
		case 0 : error_str = ERR_CODE_0; break;
		case 1 : error_str = ERR_CODE_1; break;
		case 2 : error_str = ERR_CODE_2; break;
		case 3 : error_str = ERR_CODE_3; break;
		case 4 : error_str = ERR_CODE_4; break;
		case 5 : error_str = ERR_CODE_5; break;
		case 6 : error_str = ERR_CODE_6; break;
		case 7 : error_str = ERR_CODE_7; break;
		case 8 : error_str = ERR_CODE_8; break;
		default : error_str = ERR_CODE_DEFAULT; break;
	}
	
	throw std::runtime_error(error_str);
}