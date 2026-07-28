# pragma once

# include <scop.hpp>
# include <vector>
# include <map>

typedef struct meshData {

	std::vector<vec3>	vertices;
	std::vector<vec2>	textureCoord;
	std::vector<vec3i>	indexes;

} t_meshData;

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
		void	_parseFile(const char* objFile, meshData &data) const;
		void	_parseVertex(const std::string &line, meshData &data) const;
		// void 	_parseVertexTexture(const std::string &line, meshData &data) const;
		void	_parseIndex(const std::string &line, meshData &data) const;

		Mesh() = delete;								//Default constructor
		Mesh	&operator=(const Mesh &other) = delete;	//Assignement operator
		Mesh(const Mesh &other) = delete;				//Copy constructor

	public:

		void			draw() const;

		Mesh(const char* objFile);
		virtual 	~Mesh();						//Destructor
};
		
