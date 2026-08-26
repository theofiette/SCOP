# pragma once

// # include "scop.hpp"
# include <vector>
# include <map>
# include <experimental/random>
# include <ostream>
# include <unordered_map>
# include "define.hpp"
# include "structs.hpp"
# include "prototype.hpp"

class Mesh
{
	private:

		unsigned int _vertexCount;
		unsigned int _indexCount;

		unsigned int _VAO;
		unsigned int _VBO;
		unsigned int _EBO;

		Transform	_transform;

		void	_generateVerticesBuffer(
			const objFileData &data, std::vector<Vertex> &vertices, std::vector<vec3<unsigned int>> &indexes) const;

		// Parsing methods called at instanciation
		void	_parseFile(const char* objFile, objFileData &data) const;
		void	_parseVertexCoordinate(const std::string &line, objFileData &data) const;
		void 	_parseVertexTexture(const std::string &line, objFileData &data) const;
		void 	_parseVertexNormal(const std::string &line, objFileData &data) const;
		void	_parseIndex(const std::string &line, objFileData &data) const;

		// Mesh alterating functions
		void	_colorFacesGrey(std::vector<Vertex> &vertices) const;
		void	_colorFacesFun(std::vector<Vertex> &vertices) const;
		void	_setOriginAtCenter(std::vector<Vertex> &vertices) const;

		Mesh() = delete;								//Default constructor
		Mesh	&operator=(const Mesh &other) = delete;	//Assignment operator
		Mesh(const Mesh &other) = delete;				//Copy constructor

	public:

		Transform	&getTransform();
		mat4x4		constructTransformationMatrix() const;
		void		draw() const;

		Mesh(const char* objFile);
		virtual 	~Mesh();						//Destructor
};
		
