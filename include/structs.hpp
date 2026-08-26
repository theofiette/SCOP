#pragma once

# include "opengl.hpp"
# include <ostream>
# include <vector>

template <typename T>
struct vec2 {
	T	x;
	T	y;


	vec2() : x{0}, y{0} {};
	vec2(T _x, T _y) : x{_x}, y{_y} {};

	bool operator==(const vec2 &other) const {
		return (
		x == other.x &&
		y == other.y
	);}

	T &operator[](unsigned int index) {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			default:
				throw (std::out_of_range("vec2 invalid index"));
		}
	}

	T operator[](unsigned int index) const {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			default:
				throw (std::out_of_range("vec2 invalid index"));
		}
	}
};

template <typename T> 
struct vec3 
{
	T	x;
	T	y;
	T	z;

	vec3() : x{0}, y{0}, z{0} {};

	vec3(T _x, T _y, T _z) : x{_x}, y{_y}, z{_z} {};

	vec3	operator/(const float unit) const {
		return (vec3(x / unit, y / unit, z / unit));
	}

	vec3	operator-(const vec3 other) const {
		return (vec3(x - other.x, y - other.y, z - other.z));
	}

	bool operator==(const vec3 &other) const {
		return (
			x == other.x &&
			y == other.y &&
			z == other.z
	);}

	T &operator[](unsigned int index) {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			case (2):
				return (z);
			default:
				throw (std::out_of_range("vec3 invalid index"));
		}
	}

	T operator[](unsigned int index) const {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			case (2):
				return (z);
			default:
				throw (std::out_of_range("vec3 invalid index"));
		}
	}


	friend std::ostream &operator<<(std::ostream &os, vec3 &vec) {
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return (os);
	}
};

typedef union mat4x4 {

	struct {

		float _00, _01, _02, _03;
		float _10, _11, _12, _13;
		float _20, _21, _22, _23;
		float _30, _31, _32, _33;

	};
	struct {

		float	m[16];
		
	};
	struct {
		float   mat[4][4];
	};

	mat4x4	&operator*(mat4x4 &other) {
		
		// safety check 

		mat4x4	retval = {};

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
					retval.mat[i][j] += mat[i][k] * other.mat[k][j];
				
			}
		}

		*this = retval;
		return (*this);
	}

} mat4x4;

# define MAT4X4(x)	mat4x4 {	x, x, x, x, \
								x, x, x, x, \
								x, x, x, x, \
								x, x, x, x}

# define MAT4X4_IDENTITY	mat4x4 {	1, 0, 0, 0, \
										0, 1, 0, 0, \
										0, 0, 1, 0, \
										0, 0, 0, 1}

# define MAT4X4_UNIFORM_SCALE(x)	mat4x4 {	x, 0, 0, 0, \
												0, x, 0, 0, \
												0, 0, x, 0, \
												0, 0, 0, 1	}

# define MAT4X4_TRANSLATION(vec3)	mat4x4 {	1, 0, 0, vec3.x, \
												0, 1, 0, vec3.y, \
												0, 0, 1, vec3.z, \
												0, 0, 0, 1	}

# define MAT4X4_ROTATION_X(angle)	mat4x4 {	1, 0, 0, 0, \
												0, cosf(angle), -sinf(angle), 0, \
												0, sinf(angle), cosf(angle), 0, \
											 	0, 0, 0, 1	}

# define MAT4X4_ROTATION_Y(angle)	mat4x4 {	cosf(angle), 0, sinf(angle), 0, \
												0, 1, 0, 0, \
												-sinf(angle), 0, cosf(angle), 0, \
												0, 0, 0, 1	}

# define MAT4X4_ROTATION_Z(angle)	mat4x4 {	cosf(angle), -sinf(angle), 0, 0, \
												sinf(angle), cosf(angle), 0, 0, \
												0, 0, 1, 0, \
												0, 0, 0, 1	}


// struct vec4ui {
// 	unsigned int	x;
// 	unsigned int	y;
// 	unsigned int	z;
// 	unsigned int	a;
// };

struct Vertex {

	vec3<float>	position;
	vec2<float>	texture;
	vec3<float>	normal;
	vec3<float>	color;
	vec3<float>	normalColor;

	bool operator==(const Vertex &other) const {
		return (
			position == other.position &&
			texture == other.texture &&
			normal == other.normal &&
			color == other.color &&
			normalColor == other.normalColor
		);}
};

struct Face {

	Vertex a;
	Vertex b;
	Vertex c;

	Vertex	&operator[](int index) {
		switch (index) {
			case (0):
				return (a);
			case (1):
				return (b);
			case (2):
				return (c);
			default:
				throw (std::out_of_range("Face invalid index"));
		}
	}
};

// ------------------------------------------------------------

// This part of the code has been generated with IA and reworked

static std::size_t hashCombine(std::size_t h, std::size_t next)
{
	return (h ^ (next + GOLDEN_RATIO + (h << 6) + (h >> 2)));
}

struct VertexHash
{
	std::size_t operator()(const Vertex &v) const
	{
		std::size_t h;
		
		h =	std::hash<float>()(v.position.x);
		h =	hashCombine(h, std::hash<float>()(v.position.y));
		h = hashCombine(h, std::hash<float>()(v.position.z));
		h = hashCombine(h, std::hash<float>()(v.texture.x));
		h = hashCombine(h, std::hash<float>()(v.texture.y));
		h = hashCombine(h, std::hash<float>()(v.normal.x));
		h = hashCombine(h, std::hash<float>()(v.normal.y));
		h = hashCombine(h, std::hash<float>()(v.normal.z));
		h = hashCombine(h, std::hash<float>()(v.color.x));
		h = hashCombine(h, std::hash<float>()(v.color.y));
		h = hashCombine(h, std::hash<float>()(v.color.z));

		return h;
	}
};

//-------------------------------------------------------------

struct Transform {
	vec3<float> translation;
	vec3<float>	rotation;
	vec3<float> scale;

	Transform(vec3<float> pos, vec3<float> rot, vec3<float> sca) : 
	translation(pos), rotation(rot), scale(sca) {};

	Transform() {};
};

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

enum textureDisplay {COLOR, TEXTURE};
enum colorDisplay	{GREY, NORMAL};

// The variables carried through the code
// Used when user input cannot be processed right away
struct registre {
	int				zMarker;
	textureDisplay	texDisplay;
	bool			textureToggle;
	float			textureCoef;
	colorDisplay	colDisplay;
	bool			normalToggle;
};