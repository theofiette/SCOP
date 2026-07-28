
#include "Mesh.hpp"

// CONSTRUCTORS

//TODO  : should parse normal and material
/*
*	This function parse a vertice line in a .obj file and fill a vec3 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
void Mesh::_parseVertex(const std::string &line, meshData &data) const {

	vec3				vertex;
	std::stringstream	stream(line);
	std::string			token;

	stream >> token;

	for (unsigned int i = 0; i < 3; i++)
	{
		stream >> token;		
		(reinterpret_cast<float *>(&vertex))[i] = std::atof(token.c_str());
	}

	data.vertices.push_back(vertex);

	// std::cout << "REGISTERED A VERTEX " << 
	// 				" X : " << vertex.x <<
	// 				" Y : " << vertex.y <<
	// 				" Z : " << vertex.z << std::endl;
}

/*
*	This function parse a vertice texture line in a .obj file and fill a vec2 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
// void Mesh::_parseVertexTexture(const std::string &line, meshData &data) const {

// 	vec2				textureCoord;
// 	std::stringstream	stream(line);
// 	std::string			token;

// 	stream >> token;

// 	for (unsigned int i = 0; i < 2; i++)
// 	{
// 		stream >> token;
// 		(reinterpret_cast<float *>(&textureCoord))[i] = std::atof(token.c_str());
// 	}

// 	data.textureCoord.push_back(textureCoord);

// 	std::cout << "REGISTERED A TEXTURE COORD " << 
// 					" X : " << textureCoord.x <<
// 					" Y : " << textureCoord.y << std::endl;

// }

/*
*	This function parse an index line in a .obj file and fill a vec3 in the mesh data
*	It splits 1 quad into 2 triangles, BUT it doesn't check that the resulting quad makes sense
*	If the face indexes are not set in a logical order, the resulting triangles will overlap.
*/
void Mesh::_parseIndex(const std::string &line, meshData &data) const {

	vec3i index;
	std::stringstream	stream(line);
	std::string			token;
	
	stream >> token;

	for (unsigned int i = 0; i < 3; i++)
	{
		stream >> token;
		(reinterpret_cast<int *>(&index))[i] = std::atoi(token.c_str());
	}

	data.indexes.push_back(index);

	stream >> token;
	if (stream.peek() != -1)
	{
		std::cout << "Splitting the quad : " << line << std::endl;

		// std::cout << "REGISTERED AN INDEX " << 
		// 		" X : " << index.x <<
		// 		" Y : " << index.y <<
		// 		" Z : " << index.z << std::endl;


		(reinterpret_cast<int *>(&index))[1] = std::atoi(token.c_str());
		data.indexes.push_back(index);

		// std::cout << "REGISTERED AN INDEX " << 
		// 			" X : " << index.x <<
		// 			" Y : " << index.y <<
		// 			" Z : " << index.z << std::endl;
	}

	
}

using ParseFunc = void (Mesh::*)(const std::string&, meshData&) const;

void Mesh::_parseFile(const char* objFile, meshData &data) const
{

	static const std::map<std::string, ParseFunc>	parseMap = {
		{"v",	&Mesh::_parseVertex},
		// {"vt",	&Mesh::_parseVertexTexture},
		{"f",	&Mesh::_parseIndex}
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
	
	meshData	data = {};

	_parseFile(objFile, data);
	_vertexCount = data.vertices.size();
	_indexCount = data.indexes.size();

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(vec3), data.vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(vec3i), data.indexes.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void *)0);
	glEnableVertexAttribArray(0);

	std::cout
		<< "Default constructor called for class Mesh" << std::endl;
}

void	Mesh::draw() const
{
	glBindVertexArray(_VAO);

	if (_indexCount)
		glDrawElements(GL_TRIANGLES, _indexCount * 3, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
	glBindVertexArray(0);
}

// DESTRUCTOR

Mesh::~Mesh()
{
	glDeleteBuffers(3, &_VAO);
	std::cout
		<< "Destructor called for class Mesh" << std::endl;
}
