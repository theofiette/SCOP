
#include "Mesh.hpp"
#include "fileLoader.hpp"

/*
*	This function parse a vertice line in a .obj file and fill a position vec3 in the mesh data
*	This function doesn't check that the coordinates are complete
*/
void Mesh::_parseVertexCoordinate(const std::string &line, objFileData &data) const {

	vec3<float>			position = {};
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

	vec2<float>			textureCoord = {};
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

	vec3<float>			normalCoord = {};
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
*	For this project, I also have to give a texture index if none is given in the .obj
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

void	Mesh::_colorFacesGrey(std::vector<Vertex> &vertices) const
{
	vec3<float>	color;

	for (Vertex &vert : vertices)
	{
		float	offset = static_cast<float>(std::experimental::randint(-10, 10)) / static_cast<float>(std::experimental::randint(100, 200));

		color.x = 0.5 + offset;
		color.y = 0.5 + offset;
		color.z = 0.5 + offset;

		vert.color = color;
	}
}

void	Mesh::_colorFacesFun(std::vector<Vertex> &vertices) const
{

	vec3<float> color;

	for (Vertex &vert : vertices)
	{
		color.x = 0.5 + static_cast<float>(std::experimental::randint(-1, 1)) / 10.0f;
		color.y = 0.5 + static_cast<float>(std::experimental::randint(-1, 1)) / 10.0f;
		color.z = 0.5 + static_cast<float>(std::experimental::randint(-1, 1)) / 10.0f;

		vert.color = color;
	}
	
}

void	Mesh::_textureFaces(std::vector<Vertex> &vertices) const
{
	for (Vertex &vert : vertices)
	{
		vert.texture.x = vert.position.x;
		vert.texture.y = vert.position.y;
	}
}

/*
*	This could be done more efficiently through the initial file parsing, 
*	but since I find it odd to move the object origin and I believe it doesn't change much
*	on the efficiency side, for now I'll keep the logic that way for convenience.
*/
void	Mesh::_setOriginAtCenter(std::vector<Vertex> &vertices) const
{
	float	xmin = std::numeric_limits<float>::max();
	float	ymin = xmin;
	float	zmin = xmin;
	float	xmax = std::numeric_limits<float>::lowest();
	float	ymax = xmax;
	float	zmax = xmax;

	for (Vertex &vert : vertices)
	{
		if (vert.position.x < xmin)
			xmin = vert.position.x;
		if (vert.position.x > xmax)
			xmax = vert.position.x;
		if (vert.position.y < ymin)
			ymin = vert.position.y;
		if (vert.position.y > ymax)
			ymax = vert.position.y;
		if (vert.position.z < zmin)
			zmin = vert.position.z;
		if (vert.position.z > zmax)
			zmax = vert.position.z;
	}
	
	float xstep = 0;
	float ystep = 0;
	float zstep = 0;
	float xrange;
	float yrange;
	float zrange;

	if (fabs(xmax + xmin) > __DBL_EPSILON__)
	{
		xrange = (fabs(xmax) > fabs(xmin) ? fabs(xmax) + xmin : fabs(xmin) - xmax) / 2.0f;
		xstep = (fabs(xmax) > fabs(xmin) ? -xrange : xrange);
	}
	if (fabs(ymax + ymin) > __DBL_EPSILON__)
	{
		yrange = (fabs(ymax) > fabs(ymin) ? fabs(ymax) + ymin : fabs(ymin) - ymax) / 2.0f;
		ystep = (fabs(ymax) > fabs(ymin) ? -yrange : yrange);
	}
	if (fabs(zmax + zmin) > __DBL_EPSILON__)
	{
		zrange = (fabs(zmax) > fabs(zmin) ? fabs(zmax) + zmin : fabs(zmin) - zmax) / 2.0f;
		zstep = (fabs(zmax) > fabs(zmin) ? -zrange : zrange);
	}
	for (Vertex &vert : vertices)
	{
		vert.position.x += xstep;
		vert.position.y += ystep;
		vert.position.z += zstep;
	}
}

void	Mesh::_generateVerticesBuffer(
	const objFileData &data, std::vector<Vertex> &vertices, std::vector<vec3<unsigned int>> &indexes) const
{
	vec3<unsigned int>		index;
	std::unordered_map<Vertex, int, VertexHash>	verticesMap;
	unsigned int			currIndex = 0;

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

			std::unordered_map<Vertex, int, VertexHash>::iterator ite = verticesMap.find(vertex);
			if (ite == verticesMap.end())
			{
				vertices.push_back(vertex);
				verticesMap.insert({vertex, currIndex});
				index[i] = currIndex++;
			}
			else
			{
				index[i] = ite->second;
			}
		}
		indexes.push_back(index);
	}
	if (!data.multiIndex)
		_textureFaces(vertices);
	_colorFacesGrey(vertices);
	_setOriginAtCenter(vertices);
}

/*
* Mesh constructor function, based on an .obj file.
* Since the .obj is based on multi-indexing vertices and openGL doesn't allow this,
* the first step is to parse the obj file to create vectors of attributes and a vector of FaceIndexes structs.
* The second step is to create a vector of the different vertices (Vertex) struct, and a vector of index from these.
*/
Mesh::Mesh(const char* objFile)
{
	// in data (parsed in file)
	objFileData			data = {};
	// out data (reconstructed for element buffer)
	std::vector<Vertex>				vertices;
	std::vector<vec3<unsigned int>>	indexes; // 3 index de vertex par face 

	data.multiIndex = false;
	_parseFile(objFile, data);
	_generateVerticesBuffer(data, vertices, indexes);

	_vertexCount = vertices.size();
	_indexCount = indexes.size();
	
	std::cout << "There are " << _vertexCount << " different vertices" << std::endl;
	std::cout << "There are " << _indexCount << " indexes" << std::endl;
	
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(vec3<int>), indexes.data(), GL_STATIC_DRAW);

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

Transform &Mesh::getTransform()
{
	return (_transform);
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
