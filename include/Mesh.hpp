# pragma once

# include <scop.hpp>
# include <vector>
# include <map>

typedef struct objFileData {

	//Vertex attributes
	std::vector<vec3>			positions;
	std::vector<vec2>			normales;
	std::vector<vec2>			textures;
	//Faces
	std::vector<FaceIndexes>	indexes;

} t_objFileData;

class Mesh
{
	private:

		unsigned int _vertexCount;
		unsigned int _indexCount;
		unsigned int _textureCoordCount;

		unsigned int _VAO;
		unsigned int _VBO;
		unsigned int _EBO;

		// Parsing methods called at instanciation
		void	_parseFile(const char* objFile, objFileData &data) const;
		void	_parseVertex(const std::string &line, objFileData &data) const;
		// void 	_parseVertexTexture(const std::string &line, objFileData &data) const;
		void	_parseIndex(const std::string &line, objFileData &data) const;

		void	_generateVerticesBuffer(
			const objFileData &data, std::vector<Vertex> &vertices, std::vector<vec3ui> &indexes) const;


		// TODO : move in helper ?
		vec3	_getRandomGrey() const;

		Mesh() = delete;								//Default constructor
		Mesh	&operator=(const Mesh &other) = delete;	//Assignement operator
		Mesh(const Mesh &other) = delete;				//Copy constructor

	public:

		void			draw() const;

		Mesh(const char* objFile);
		virtual 	~Mesh();						//Destructor
};
		
