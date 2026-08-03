
#include "Mesh.hpp"

// CONSTRUCTORS

/*
*	This function parse a vertice line in a .obj file and fill a position vec3 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
void Mesh::_parseVertexCoordinate(const std::string &line, objFileData &data) const {

	vec3				position;
	std::stringstream	stream(line);
	std::string			prefixe;

	stream >> prefixe;

	for (unsigned int i = 0; i < 3; i++)
	{
		float	f;

		stream >> f;
		(reinterpret_cast<float *>(&position))[i] = f;
	}
	data.positions.push_back(position);
}

/*
*	This function parse a vertice texture line in a .obj file and fill a vec2 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
void Mesh::_parseVertexTexture(const std::string &line, objFileData &data) const {

	vec2				textureCoord;
	std::stringstream	stream(line);
	std::string			prefixe;

	stream >> prefixe;

	for (unsigned int i = 0; i < 2; i++)
	{
		float f;

		stream >> f;
		(reinterpret_cast<float *>(&textureCoord))[i] = f;
	}
	data.multiIndex = true;
	data.textures.push_back(textureCoord);
}

/*
*	This function parse a vertice normal line in a .obj file and fill a vec2 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
void Mesh::_parseVertexNormal(const std::string &line, objFileData &data) const {

	vec3				normalCoord;
	std::stringstream	stream(line);
	std::string			prefixe;

	stream >> prefixe;

	for (unsigned int i = 0; i < 3; i++)
	{
		float f;

		stream >> f;
		(reinterpret_cast<float *>(&normalCoord))[i] = f;
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

	FaceIndexes 		index;
	std::stringstream	stream(line);
	std::string			token;
	
	stream >> token;

	for (unsigned int i = 0; i < 3; i++)
	{
		stream >> token;
		(reinterpret_cast<int *>(&index.positionIndex))[i] = std::atoi(token.c_str()) - 1;
		if (token.find('/') != std::string::npos)
		{
			token = token.substr(token.find('/') + 1);
			(reinterpret_cast<int *>(&index.textureIndex))[i] = std::atoi(token.c_str()) - 1;
		}
		if (token.find('/') != std::string::npos)
		{
			token = token.substr(token.find('/') + 1);\
			(reinterpret_cast<int *>(&index.normalIndex))[i] = std::atoi(token.c_str()) - 1;
		}
	}

	data.indexes.push_back(index);

	stream >> token;
	if (stream.peek() != -1)
	{
		std::cout << "Splitting the quad : " << line << std::endl;

		index.positionIndex.y = index.positionIndex.x;
		index.normalIndex.y = index.normalIndex.x;
		index.textureIndex.y = index.textureIndex.x;

		(reinterpret_cast<int *>(&index))[0] = std::atoi(token.c_str()) - 1;
		(reinterpret_cast<int *>(&index))[1] = std::atoi(token.c_str()) - 1;
		(reinterpret_cast<int *>(&index))[2] = std::atoi(token.c_str()) - 1;
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


	// std::cout << "There are " << data.indexes.size() << " faces to operate on." << std::endl;

	for (const FaceIndexes &face : data.indexes)
	{
		index = {};
		for (unsigned int i = 0; i < 3; i++)
		{
			Vertex vertex = {};
			unsigned int coordIndex = reinterpret_cast<const unsigned int *>(&(face.positionIndex))[i];
			std::cout << "Needing vertex coord " << coordIndex << " / " << data.positions.size() << std::endl;
			
			vertex.position = data.positions[coordIndex];
			if (data.multiIndex)
			{
				unsigned int normalIndex = reinterpret_cast<const unsigned int *>(&(face.normalIndex))[i];
				unsigned int textureIndex = reinterpret_cast<const unsigned int *>(&(face.textureIndex))[i];

				std::cout << "Needing vertex texture " << textureIndex << " / " << data.textures.size() << std::endl;
				std::cout << "Needing vertex normal " << normalIndex << " / " << data.normals.size() << std::endl;
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
				(reinterpret_cast<unsigned int *>(&index))[i] = vertexIndex;
			}
			else 
			{
				vertices.push_back(vertex);
				(reinterpret_cast<unsigned int *>(&index))[i] = currIndex ++;
			}
			// std::cout << "Value registered is " << vertex.position.x << " | " <<
			// 										vertex.position.y << " | " <<
			// 										vertex.position.z << std::endl;
			
		}
		// std::cout << "Pushing a face with indexes : " << index.x << " | " << index.y << " | " << index.z << std::endl;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// layout 1 -> texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texture));
	glEnableVertexAttribArray(1);
	// layout 2 -> normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
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
	glDeleteBuffers(3, &_VAO);
	std::cout
		<< "Destructor called for class Mesh" << std::endl;
}
