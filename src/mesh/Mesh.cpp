#include "mesh/Mesh.hpp"

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
	data.textureIndex = true;
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
	data.normalIndex = true;
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
	if (stream >> token)
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


void Mesh::_parseFile(const char* objFile, objFileData &data) const
{
	using ParseFunc = void (Mesh::*)(const std::string&, objFileData&) const;

	static const std::map<std::string, ParseFunc>	parseMap = {
		{"v",	&Mesh::_parseVertexCoordinate},
		{"vn",	&Mesh::_parseVertexNormal},
		{"vt",	&Mesh::_parseVertexTexture},
		{"f",	&Mesh::_parseIndex}
	};

	if (fileLoader::getExtension(objFile) != ".obj")
		clean_exit(true, 8);

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

vec3<float> Mesh::_calculateNormal(Face &face) const
{
	vec3<float> edge1, edge2;

	edge1 = face[1].position - face[0].position;
	edge2 = face[2].position - face[0].position;

	return (vectorMath::normalize(vectorMath::cross(edge1, edge2)));
}

void	Mesh::_applyNormalColor(Face &face, bool projectTexture) const
{
	vec3<float> normal = _calculateNormal(face);

	for (int i = 0; i < 3; i++)
	{
		Vertex *vert = &face[i];

		if (fabs(normal.x) >= fabs(normal.y) && fabs(normal.x) >= fabs(normal.z))
		{
			if (projectTexture)
				vert->texture = vec2<float>(vert->position.z, vert->position.y);
			vert->normalColor = vec3(1.0f, 0.0f, 0.0f);
		}
		else if (fabs(normal.y) >= fabs(normal.x) && fabs(normal.y) >= fabs(normal.z))
		{
			if (projectTexture)
				vert->texture = vec2<float>(vert->position.x, vert->position.z);
			vert->normalColor = vec3(0.0f, 1.0f, 0.0f);
		}
		else
		{
			if (projectTexture)
				vert->texture = vec2<float>(vert->position.x, vert->position.y);
			vert->normalColor = vec3(0.0f, 0.0f, 1.0f);
		}
	}
}

void	Mesh::_getBoundingBox(
	const std::vector<Vertex> &vertices, vec3<float> &min, vec3<float> &max) const
{
	min = vec3<float>(std::numeric_limits<float>::max());
	max = vec3<float>(std::numeric_limits<float>::lowest());

	for (const Vertex &vert : vertices)
	{
		for (int i = 0; i < 3; i++)
		{
			if (vert.position[i] < min[i])
				min[i] = vert.position[i];
			if (vert.position[i] > max[i])
				max[i] = vert.position[i];
		}
	}
}

void	Mesh::_setOriginAtCenter(std::vector<Vertex> &vertices, 
	const vec3<float> &min, const vec3<float> &max) const
{
	
	vec3<float> steps = {};

	for (int i = 0; i < 3; i++)
	{
		if (fabs(max[i] + min[i]) > std::numeric_limits<float>::epsilon())
			steps[i] = (min[i] + max[i]) / 2;
	}
		
	for (Vertex &vert : vertices)
	{
		vert.position -= steps;
	}
}

void	Mesh::_scaleToMatchWindow(Transform &transform, 
	const vec3<float> &min, const vec3<float> &max)
{

	vec3<float> range(max - min);
	float		maxRange;
	float		scaleFactor;
	
	maxRange = range.max();
	if (maxRange < std::numeric_limits<float>::epsilon())
		return ;

	scaleFactor = SCALE_TARGET / maxRange;
	// scaleFactor = maxRange / SCALE_TARGET;
	transform.scale = vec3(scaleFactor);
	transform.translation.z = Z_INIT_TRANS;

}

void	Mesh::_generateVerticesBuffer(const objFileData &data, 
	std::vector<Vertex> &vertices, std::vector<vec3<unsigned int>> &indexes) const
{
	vec3<unsigned int>							index;
	std::unordered_map<Vertex, int, VertexHash>	verticesMap;
	unsigned int								currIndex = 0;

	for (const FaceIndexes &faceIndex : data.indexes)
	{
		index = {};
		Face face = {};

		for (unsigned int i = 0; i < 3; i++)
		{
			Vertex vertex = {};

			unsigned int coordIndex = faceIndex.positionIndex[i];
			vertex.position = data.positions[coordIndex];

			if (data.textureIndex)
			{
				unsigned int textureIndex = faceIndex.textureIndex[i];
				vertex.texture = data.textures[textureIndex];
			}
			if (data.normalIndex)
			{
				unsigned int normalIndex = faceIndex.normalIndex[i];
				vertex.normal = data.normals[normalIndex];
			}
			face[i] = vertex;
		}

		_applyNormalColor(face, !data.textureIndex);

		for (unsigned int i = 0; i < 3; i++)
		{
			Vertex vertex = face[i];

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
}

/*
* Mesh constructor function, based on an .obj file.
* Since the .obj is based on multi-indexing vertices and openGL doesn't allow this,
* the first step is to parse the obj file to create vectors of attributes and a vector of FaceIndexes structs.
* The second step is to create a vector of the different vertices (Vertex) struct, and a vector of index from these.
*/
Mesh::Mesh(const char* objFile) :
_transform(vec3<float>(0.0, 0.0, -5.0), vec3<float>(0.0, 0.0, 0.0), vec3<float>(1.0, 1.0, 1.0))
{
	// in data (parsed in file)
	objFileData						data = {};
	// out data (reconstructed for element buffer)
	std::vector<Vertex>				vertices;
	std::vector<vec3<unsigned int>>	indexes; 

	data.textureIndex = false;
	data.normalIndex = false;
	_parseFile(objFile, data);
	_generateVerticesBuffer(data, vertices, indexes);

	vec3<float> min, max;
	_getBoundingBox(vertices, min, max);
	_colorFacesGrey(vertices);
	_setOriginAtCenter(vertices, min, max);
	_scaleToMatchWindow(_transform, min, max);

	_vertexCount = vertices.size();
	_indexCount = indexes.size();
	
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(vec3<unsigned int>), indexes.data(), GL_STATIC_DRAW);

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
	// layout 4 -> normalColor
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normalColor));
	glEnableVertexAttribArray(4);
}

mat4x4	Mesh::constructTransformationMatrix() const
{
	mat4x4 transformation;

	mat4x4 scale_matrix;
	mat4x4 translation_matrix;
	mat4x4 rotation_matrix;
	
	mat4x4 rotation_x_matrix;
	mat4x4 rotation_y_matrix;
	mat4x4 rotation_z_matrix;
	
	translation_matrix = MAT4X4_TRANSLATION(_transform.translation);
	scale_matrix = MAT4X4_SCALE(_transform.scale);
	rotation_x_matrix = MAT4X4_ROTATION_X(_transform.rotation.x);
	rotation_y_matrix = MAT4X4_ROTATION_Y(_transform.rotation.y);
	rotation_z_matrix = MAT4X4_ROTATION_Z(_transform.rotation.z);
	rotation_matrix = rotation_z_matrix * rotation_y_matrix * rotation_x_matrix;
	transformation = translation_matrix * rotation_matrix * scale_matrix;

	return (transformation);
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
}
