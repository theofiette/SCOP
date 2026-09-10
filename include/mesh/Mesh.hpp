# pragma once

// # include "scop.hpp"
# include <vector>
# include <map>
# include <experimental/random>
# include <ostream>
# include <unordered_map>

# include "core/define.hpp"
# include "core/opengl.hpp"
# include "core/prototype.hpp"

# include "loader/fileLoader.hpp"
# include "math/mat.hpp"
# include "math/vectorMath.hpp"
# include "mesh/Vertex.hpp"
# include "mesh/Face.hpp"

struct FaceIndexes {
	vec3<unsigned int>	positionIndex;
	vec3<unsigned int>	textureIndex;
	vec3<unsigned int>	normalIndex;
};

struct objFileData {

	//Vertex attributes
	std::vector<vec3<float>>	positions;
	std::vector<vec2<float>>	textures;
	std::vector<vec3<float>>	normals;
	//Faces
	std::vector<FaceIndexes>	indexes;
	//Are there texture and normal coordinates ?
	bool						textureIndex;
	bool						normalIndex;

};

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
			const objFileData &data, 
			std::vector<Vertex> &vertices, 
			std::vector<vec3<unsigned int>> &indexes) const;

		// Parsing methods called at instanciation
		void	_parseFile(const char* objFile, objFileData &data) const;
		void	_parseVertexCoordinate(const std::string &line, objFileData &data) const;
		void 	_parseVertexTexture(const std::string &line, objFileData &data) const;
		void 	_parseVertexNormal(const std::string &line, objFileData &data) const;
		void	_parseIndex(const std::string &line, objFileData &data) const;

		// Mesh alterating functions
		void		_colorFacesGrey(std::vector<Vertex> &vertices) const;
		void		_applyNormalColor(Face &face, bool projectTexture) const;
		vec3<float> _calculateNormal(Face &face) const;
		void		_getBoundingBox(const std::vector<Vertex> &vertices, vec3<float> &min, vec3<float> &max) const;
		void		_setOriginAtCenter(std::vector<Vertex> &vertices, 
										const vec3<float> &min, const vec3<float> &max) const;
		void		_scaleToMatchWindow(Transform &transform, const vec3<float> &min, const vec3<float> &max);
		

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
		
