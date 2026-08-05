# pragma once

# include "scop.hpp"
# include <vector>
# include <map>
# include <experimental/random>

struct objFileData {

	//Vertex attributes
	std::vector<vec3<float>>			positions;
	std::vector<vec2<float>>			textures;
	std::vector<vec3<float>>			normals;
	//Faces
	std::vector<FaceIndexes>	indexes;
	//Are there texture and normal coordinates ?
	bool						multiIndex;

};

class Mesh
{
	private:

		unsigned int _vertexCount;
		unsigned int _indexCount;
		// unsigned int _textureCoordCount;

		unsigned int _VAO;
		unsigned int _VBO;
		unsigned int _EBO;

		// Parsing methods called at instanciation
		void	_parseFile(const char* objFile, objFileData &data) const;
		void	_parseVertexCoordinate(const std::string &line, objFileData &data) const;
		void 	_parseVertexTexture(const std::string &line, objFileData &data) const;
		void 	_parseVertexNormal(const std::string &line, objFileData &data) const;
		void	_parseIndex(const std::string &line, objFileData &data) const;

		void	_colorFaces(std::vector<Vertex> &vertices) const;

		void	_generateVerticesBuffer(
			const objFileData &data, std::vector<Vertex> &vertices, std::vector<vec3<unsigned int>> &indexes) const;

		Mesh() = delete;								//Default constructor
		Mesh	&operator=(const Mesh &other) = delete;	//Assignment operator
		Mesh(const Mesh &other) = delete;				//Copy constructor

	public:

		void			draw() const;

		Mesh(const char* objFile);
		virtual 	~Mesh();						//Destructor
};
		
