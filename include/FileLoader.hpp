# pragma once

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

#include "scop.hpp"

class FileLoader
{
	private:

		FileLoader(); 	//Default constructor is not allowed

public:

	static std::string	toString(const char *path);
	static std::string	getExtension(const char *path);

};
		
