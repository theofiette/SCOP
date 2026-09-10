#pragma once

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <vector>

// #include "scop.hpp"

namespace fileLoader {

	std::string	 toString(const char *path);

	std::vector<std::string> toStringVector(const char *path);

	std::string	getExtension(const char *path);

}
