#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

template <typename T>
struct vec2 {
	T	x;
	T	y;

	bool operator==(vec2 &other) const {
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

} mat4x4;

# define MAT4X4(x) mat4x4 {x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x}
# define MAT4X4_IDENTITY mat4x4 {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
# define MAT4X4_UNIFORM_SCALE(x) mat4x4 {x, 0, 0, 0, 0, x, 0, 0, 0, 0, x, 0, 0, 0, 0, 1};
# define MAT4X4_TRANSLATION(vec3) mat4x4 {1, 0, 0, vec3.x, 0, 1, 0, vec3.y, 0, 0, 1, vec3.z, 0, 0, 0, 1};

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

	bool operator==(Vertex &other) const {
		return (
			position == other.position &&
			texture == other.texture &&
			normal == other.normal &&
			color == other.color
		);}
};

struct FaceIndexes {
	vec3<unsigned int>	positionIndex;
	vec3<unsigned int>	textureIndex;
	vec3<unsigned int>	normalIndex;
};