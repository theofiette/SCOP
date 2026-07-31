
#include "Mesh.hpp"

// CONSTRUCTORS

/*
*	This function parse a vertice line in a .obj file and fill a position vec3 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
void Mesh::_parseVertexCoordinate(const std::string &line, objFileData &data) const {

	vec3				position;
	std::stringstream	stream(line);
	std::string			token;

	stream >> token;

	for (unsigned int i = 0; i < 3; i++)
	{
		float	f;

		stream >> f;
		(reinterpret_cast<float *>(&position))[i] = f;
	}

	position.y -= 3.0;
	position.z -= 4;

	data.positions.push_back(position);

	// std::cout << "REGISTERED A VERTEX " << 
	// 				" X : " << vertex.x <<
	// 				" Y : " << vertex.y <<
	// 				" Z : " << vertex.z << std::endl;
}

/*
*	This function parse a vertice texture line in a .obj file and fill a vec2 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
// void Mesh::_parseVertexTexture(const std::string &line, objFileData &data) const {

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
*	This function parse an index line in a .obj file and fill a FaceIndex struct in the mesh data
*	It splits 1 quad into 2 triangles, BUT it doesn't check that the resulting quad makes sense
*	If the face indexes are not set in a logical order, the resulting triangles will overlap.
*
*	FOR NOW, this doesn't register vn or vt indexes
*/
void Mesh::_parseIndex(const std::string &line, objFileData &data) const {

	FaceIndexes 		index;
	std::stringstream	stream(line);
	std::string			token;
	
	stream >> token;

	for (unsigned int i = 0; i < 3; i++)
	{
		stream >> token;
		(reinterpret_cast<int *>(&index.positionIndex))[i] = std::atoi(token.c_str()) - 1;
	}

	data.indexes.push_back(index);

	stream >> token;
	if (stream.peek() != -1)
	{
		std::cout << "Splitting the quad : " << line << std::endl;

		index.positionIndex.y = index.positionIndex.x;
		(reinterpret_cast<int *>(&index))[0] = std::atoi(token.c_str()) - 1;
		data.indexes.push_back(index);

	}
}

using ParseFunc = void (Mesh::*)(const std::string&, objFileData&) const;

void Mesh::_parseFile(const char* objFile, objFileData &data) const
{

	static const std::map<std::string, ParseFunc>	parseMap = {
		{"v",	&Mesh::_parseVertexCoordinate},
		// {"vn",	Mesh::_parseVertexNormale},
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

// TODO : check out of bound for vector
// TODO : check if repeat
void	Mesh::_generateVerticesBuffer(
	const objFileData &data, std::vector<Vertex> &vertices, std::vector<vec3ui> &indexes) const
{
	// Map de vertices crees ??
	// Vertex 			vertex;
	vec3ui			index;
	unsigned int	currIndex = 0;


	// std::cout << "There are " << data.indexes.size() << " faces to operate on." << std::endl;

	for (const FaceIndexes &face : data.indexes)
	{
		index = {};
		for (unsigned int i = 0; i < 3; i++)
		{
			Vertex vertex = {};
			// check if there is already an existing vertex with the same attributes
			// if yes : simply add its index to the indexes (index[i])
			// else :
			unsigned int coordIndex = reinterpret_cast<const unsigned int *>(&(face.positionIndex))[i];
			// std::cout << "Needing vertex coord " << coordIndex << std::endl;
			vertex.position = data.positions[coordIndex];
			// std::cout << "Value registered is " << vertex.position.x << " | " <<
			// 										vertex.position.y << " | " <<
			// 										vertex.position.z << std::endl;
			vertex.color = _getRandomGrey();
			vertices.push_back(vertex);
			
			(reinterpret_cast<unsigned int *>(&index))[i] = currIndex ++;
		}
		// std::cout << "Pushing a face with indexes : " << index.x << " | " << index.y << " | " << index.z << std::endl;
		indexes.push_back(index);
	}
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

	_parseFile(objFile, data); 							// Remplir la struct objFileData
	_generateVerticesBuffer(data, vertices, indexes);	// Creer un vecteur de vertices + un vecteur de 3 indice de vertice par face


	// std::cout << "\n\nAFTER REMAPPING :" << std::endl;

	// for (unsigned int i = 0; i < indexes.size(); i++)
	// {
	// 	std::cout << "\nFace info : " << std::endl;

	// 	Vertex vert;

		// vert = vertices[indexes[i].x];
		// std::cout << "Vertex at index " << indexes[i].x << "is : " << std::endl;
		// std::cout << "x : " << vert.position.x << "\n" <<
		// 			 "y : " << vert.position.y << "\n" <<
		// 			 "z : " << vert.position.z << std::endl;
		
		// vert = vertices[indexes[i].y];
		// std::cout << "Vertex at index " << indexes[i].y << "is : " << std::endl;
		// std::cout << "x : " << vert.position.x << "\n" <<
		// 			 "y : " << vert.position.y << "\n" <<
		// 			 "z : " << vert.position.z << std::endl;

	// 	vert = vertices[indexes[i].z];
	// 	std::cout << "Vertex at index " << indexes[i].z << "is : " << std::endl;
	// 	std::cout << "x : " << vert.position.x << "\n" <<
	// 				 "y : " << vert.position.y << "\n" <<
	// 				 "z : " << vert.position.z << std::endl;
	// }
	_vertexCount = vertices.size();
	_indexCount = indexes.size();

	std::cout << "\nVertex count is " << _vertexCount << std::endl;
	std::cout << "Index count is " << _indexCount << std::endl;

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(vec3i), indexes.data(), GL_STATIC_DRAW);

	// layout 0 -> position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	glEnableVertexAttribArray(0);
	// layout 1 -> normal
	// ....
	// layout 2 -> texture
	// ....
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

//TODO : out of class
# include <experimental/random>
vec3	Mesh::_getRandomGrey() const
{
	vec3	color;
	// float	offset = static_cast<float>(std::experimental::randint(-1, 1)) / static_cast<float>(std::experimental::randint(10, 20));

	// color.x = 0.5 + offset;
	// color.y = 0.5 + offset;
	// color.z = 0.5 + offset;

	color.x = 0.5 + static_cast<float>(std::experimental::randint(-1, 1)) / 10.0f;
	color.y = 0.5 + static_cast<float>(std::experimental::randint(-1, 1)) / 10.0f;
	color.z = 0.5 + static_cast<float>(std::experimental::randint(-1, 1)) / 10.0f;

	return (color);
}

// DESTRUCTOR

Mesh::~Mesh()
{
	glDeleteBuffers(3, &_VAO);
	std::cout
		<< "Destructor called for class Mesh" << std::endl;
}
