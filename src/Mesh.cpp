
#include "Mesh.hpp"

// CONSTRUCTORS

/*
*	This function parse a vertice line in a .obj file and fill a position vec3 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
void Mesh::_parseVertexCoordinate(const std::string &line, objFileData &data) const {

	vec3				position = {};
	std::stringstream	stream(line);
	std::string			prefixe;

	stream >> prefixe;

	for (unsigned int i = 0; i < 3; i++)
	{
		float	f;

		stream >> f;
		position[i] = f;
	}
	data.positions.push_back(position);
}

/*
*	This function parse a vertice texture line in a .obj file and fill a vec2 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
void Mesh::_parseVertexTexture(const std::string &line, objFileData &data) const {

	vec2				textureCoord = {};
	std::stringstream	stream(line);
	std::string			prefixe;

	stream >> prefixe;

	for (unsigned int i = 0; i < 2; i++)
	{
		float f;

		stream >> f;
		textureCoord[i] = f;
	}
	data.multiIndex = true;
	data.textures.push_back(textureCoord);
}

/*
*	This function parse a vertice normal line in a .obj file and fill a vec2 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
void Mesh::_parseVertexNormal(const std::string &line, objFileData &data) const {

	vec3				normalCoord = {};
	std::stringstream	stream(line);
	std::string			prefixe;

	stream >> prefixe;

	for (unsigned int i = 0; i < 3; i++)
	{
		float f;

		stream >> f;
		normalCoord[i] = f;
	}
	data.multiIndex = true;
	data.normals.push_back(normalCoord);
}

/*
*	This function parse an index line in a .obj file and fill a FaceIndex struct in the mesh data
*	It splits 1 quad into 2 triangles, BUT it doesn't check that the resulting quad makes sense
*	If the face indexes are not set in a logical order, the resulting triangles will overlap.
*
*/
void Mesh::_parseIndex(const std::string &line, objFileData &data) const {

	FaceIndexes 		index = {};
	std::stringstream	stream(line);
	std::string			token;
	
	stream >> token;

	for (unsigned int i = 0; i < 3; i++)
	{
		stream >> token;
		index.positionIndex[i] = std::atoi(token.c_str()) - 1;
		if (token.find('/') != std::string::npos)
		{
			token = token.substr(token.find('/') + 1);
			if (token[0] != '/')
				index.textureIndex[i] = std::atoi(token.c_str()) - 1;
		}
		if (token.find('/') != std::string::npos)
		{
			token = token.substr(token.find('/') + 1);
			index.normalIndex[i] = std::atoi(token.c_str()) - 1;
		}
	}

	data.indexes.push_back(index);

	// 4th position -> splitting the quad
	stream >> token;
	if (stream.peek() != -1)
	{
		index.positionIndex.y = index.positionIndex.x;
		index.normalIndex.y = index.normalIndex.x;
		index.textureIndex.y = index.textureIndex.x;

		index.positionIndex.x = std::atoi(token.c_str()) - 1;
		if (token.find('/') != std::string::npos)
		{
			token = token.substr(token.find('/') + 1);
			if (token[0] != '/')
				index.textureIndex.x = std::atoi(token.c_str()) - 1;
		}
		if (token.find('/') != std::string::npos)
		{
			token = token.substr(token.find('/') + 1);
			index.normalIndex.x = std::atoi(token.c_str()) - 1;
		}
		data.indexes.push_back(index);
	}
}

using ParseFunc = void (Mesh::*)(const std::string&, objFileData&) const;

void Mesh::_parseFile(const char* objFile, objFileData &data) const
{

	static const std::map<std::string, ParseFunc>	parseMap = {
		{"v",	&Mesh::_parseVertexCoordinate},
		{"vn",	&Mesh::_parseVertexNormal},
		{"vt",	&Mesh::_parseVertexTexture},
		{"f",	&Mesh::_parseIndex}
	};

	std::vector<std::string>	fileContent = fileLoader::toStringVector(objFile);


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

void	Mesh::_colorFaces(std::vector<Vertex> &vertices) const
{
	for (Vertex &vert : vertices)
	{
		vec3	color;
		// float	offset = static_cast<float>(std::experimental::randint(-10, 10)) / static_cast<float>(std::experimental::randint(100, 200));

		// color.x = 0.5 + offset;
		// color.y = 0.5 + offset;
		// color.z = 0.5 + offset;

		color.x = 0.5 + static_cast<float>(std::experimental::randint(-1, 1)) / 10.0f;
		color.y = 0.5 + static_cast<float>(std::experimental::randint(-1, 1)) / 10.0f;
		color.z = 0.5 + static_cast<float>(std::experimental::randint(-1, 1)) / 10.0f;

		vert.color = color;
	}
}

void	Mesh::_generateVerticesBuffer(
	const objFileData &data, std::vector<Vertex> &vertices, std::vector<vec3ui> &indexes) const
{
	vec3ui			index;
	unsigned int	currIndex = 0;

	for (const FaceIndexes &face : data.indexes)
	{
		index = {};
		for (unsigned int i = 0; i < 3; i++)
		{
			Vertex vertex = {};
			unsigned int coordIndex = face.positionIndex[i];
			
			vertex.position = data.positions[coordIndex];
			if (data.multiIndex)
			{
				unsigned int textureIndex = face.textureIndex[i];
				unsigned int normalIndex = face.normalIndex[i];

				vertex.texture = data.textures[textureIndex];
				vertex.normal = data.normals[normalIndex];
			}

			unsigned int vertexIndex = 0;
			for (const Vertex &vert : vertices)
			{
				if (vert == vertex)
					break ;
				vertexIndex ++;
			};
			if (vertexIndex < vertices.size())
			{
				index[i] = vertexIndex;
			}
			else 
			{
				vertices.push_back(vertex);
				index[i] = currIndex ++;
			}
		}
		indexes.push_back(index);
	}
	_colorFaces(vertices);
}

/*
* Mesh constructor function, based on an .obj file.
* Since the .obj is based on multi-indexing vertices and openGL doesn't allow this,
* the first step is to parse the obj file to create vectors of attributes and a vector of FaceIndexes structs.
* The second step is to create a vector of the different vertices (Vertex) struct, and a vector of 
* a vector of index from these.
*/
Mesh::Mesh(const char* objFile)
{
	// in data (parsed in file)
	objFileData			data = {};
	// out data (reconstructed for element buffer)
	std::vector<Vertex>			vertices;
	std::vector<vec3ui>			indexes; // 3 index de vertex par face 

	data.multiIndex = false;
	_parseFile(objFile, data); 							// Remplir la struct objFileData
	_generateVerticesBuffer(data, vertices, indexes);	// Creer un vecteur de vertices + un vecteur de 3 indice de vertice par face

	_vertexCount = vertices.size();
	_indexCount = indexes.size();

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(vec3i), indexes.data(), GL_STATIC_DRAW);

	// layout 0 -> position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// layout 1 -> texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);
	// layout 2 -> normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	// layout 3 -> color
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
	glEnableVertexAttribArray(3);

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
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
	
	std::cout
		<< "Destructor called for class Mesh" << std::endl;
}
