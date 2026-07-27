
#include "Mesh.hpp"

// CONSTRUCTORS

void Mesh::_parseVertex(const std::string &line, meshData &data) const {

	(void)data;
	std::cout << line << " is a Vertex line" << std::endl;
}

void Mesh::_parseIndex(const std::string &line, meshData &data) const {

	(void)data;
	std::cout << line << " is a Index line" << std::endl;
}

using ParseFunc = void (Mesh::*)(const std::string&, meshData&) const;

void Mesh::_parseFile(const char* objFile, meshData &data) const
{

	static const std::map<std::string, ParseFunc>	parseMap = {
		{"v", &Mesh::_parseVertex},
		{"f", &Mesh::_parseIndex}
	};

	std::vector<std::string>	fileContent = FileLoader::toStringVector(objFile);

	for (const std::string &line : fileContent)
	{
		std::stringstream			stream(line);
		std::string					token;
		stream >> token;

		auto it = parseMap.find(token);
		if (it != parseMap.end())
		{
			ParseFunc func = it->second;
			(this->*func)(line, data);
		}
	}
}

Mesh::Mesh(const char* objFile)
{
	
	meshData	data;

	_parseFile(objFile, data);
	// std::cout << vertices << std::endl;
	// std::cout << fileContent << std::endl;


	// _VAO = 
	// _VBO =

	// if (indices)
	// _EBO =
	// else
	// _EBO =     <- ????

	std::cout
		<< "Default constructor called for class Mesh" << std::endl;
}

unsigned int	Mesh::get_VAO() const
{
	return (_VAO);
}

unsigned int	Mesh::get_VBO() const
{
	return (_VBO);
}

unsigned int	Mesh::get_EBO() const
{
	return (_EBO);
}

void	Mesh::draw() const
{
	glBindVertexArray(_VAO);
	// if (_EBO == -1)
	// {
	// 	glDrawArrays(GL_TRIANGLES, 0, _vertexCount) // VBO object ?
	// }
	// else
	// {
	// 	glDrawElements(GL_TRIANGLES, _indexesCount, GL_UNSIGNED_INT, 0 // EBO object ?
	// }
}

// DESTRUCTOR

Mesh::~Mesh()
{
	std::cout
		<< "Destructor called for class Mesh" << std::endl;
}
