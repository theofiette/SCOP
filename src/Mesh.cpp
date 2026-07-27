
#include "Mesh.hpp"

// CONSTRUCTORS

Mesh::Mesh(const char* objFile)
{
	(void)objFile;

	std::vector<vec3>	vertices;
	std::string			fileContent = FileLoader::toString(objFile);

	// std::cout << vertices << std::endl;
	std::cout << fileContent << std::endl;


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
