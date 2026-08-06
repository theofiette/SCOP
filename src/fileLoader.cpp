
#include "scop.hpp"

namespace fileLoader {

	// CONSTRUCTORS

	std::string	 toString(const char *path)
	{
		std::string			str;
		std::ifstream		file;
		std::stringstream	stream;

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {

			file.open(path);
			stream << file.rdbuf();
			file.close();
			str = stream.str();
		}
		catch (std::ifstream::failure &e) {

			std::cout << "ERROR::FILELOADER::FILE_NOT_SUCCESFULLY_READ(toString)" << std::endl;
			clean_exit(true, 1);

		}
		return (str);
	}

	std::vector<std::string> toStringVector(const char *path)
	{
		std::vector<std::string>	strVector;
		std::ifstream				file;
		std::stringstream			stream;
		std::string					line;
		std::string					word;

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		std::cout << "toStringVector" << std::endl;

		try {

			file.open(path);
			stream << file.rdbuf();

			while (stream.good() && !stream.eof())
			{
				line.clear();
				word.clear();
				while (stream >> word)
				{
					if (word.length())
						line.append(word + " ");
					while (stream.peek() == ' ')
						stream.get();
					if (stream.peek() == '\n' || stream.peek() == '\r')
						break ;
				}

				// std::cout << "line is : " << line << std::endl;
				if (line.length())
					strVector.push_back(line);
			}
		}
		catch (std::ifstream::failure &e) {

			std::cout << "ERROR::FILELOADER::FILE_NOT_SUCCESFULLY_READ(toStringVector)" << std::endl;
			clean_exit(true, 1);

		}
		return (strVector);
	}

	std::string	getExtension(const char *path)
	{
		std::string		path_str;
		std::string		extension;
		size_t			extensionMarker;

		try {

			path_str = std::string(path);
			extensionMarker = path_str.rfind(".");
			extension = path_str.substr(extensionMarker);

		}
		catch (std::exception &e) {

			std::cerr << "ERROR::TEXTURE::LOADING::FAILED\n" << "Invalid file extension" << std::endl;
			clean_exit(true, 1);

		}
		return (extension);
	}
}
