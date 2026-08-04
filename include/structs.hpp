#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct vec2 {
	float	x;
	float	y;

	bool operator==(vec2 &other) const {
		return (
		x == other.x &&
		y == other.y
	);}

	float &operator[](unsigned int index) {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			default:
				throw (std::out_of_range("vec2 invalid index"));
		}
	}

	float operator[](unsigned int index) const {
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

struct vec3 {
    float	x;
    float	y;
    float	z;

	bool operator==(vec3 &other) const {
		return (
			x == other.x &&
			y == other.y &&
			z == other.z
	);}

	float &operator[](unsigned int index) {
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

	float operator[](unsigned int index) const {
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
};

struct vec3i {
    int	x;
    int	y;
    int	z;

	bool operator==(vec3i &other) const {
		return (
			x == other.x &&
			y == other.y &&
			z == other.z
	);}

	int &operator[](unsigned int index) {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			case (2):
				return (z);
			default:
				throw (std::out_of_range("vec3i invalid index"));
		}
	}

	int operator[](unsigned int index) const {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			case (2):
				return (z);
			default:
				throw (std::out_of_range("vec3i invalid index"));
		}
	}
};

struct vec3ui {
    unsigned int	x;
    unsigned int	y;
    unsigned int	z;

	bool operator==(vec3ui &other) const {
		return (
			x == other.x &&
			y == other.y &&
			z == other.z
		);
	}

	unsigned int &operator[](unsigned int index) {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			case (2):
				return (z);
			default:
				throw (std::out_of_range("vec3ui invalid index"));
		}
	}

	unsigned int operator[](unsigned int index) const {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			case (2):
				return (z);
			default:
				throw (std::out_of_range("vec3ui invalid index"));
		}
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

// struct vec4ui {
// 	unsigned int	x;
// 	unsigned int	y;
// 	unsigned int	z;
// 	unsigned int	a;
// };

struct Vertex {
    vec3	position;
    vec2 	texture;
    vec3 	normal;
	vec3	color;

	bool operator==(Vertex &other) const {
		return (
			position == other.position &&
			texture == other.texture &&
			normal == other.normal &&
			color == other.color
		);}
};

struct FaceIndexes {
	vec3ui	positionIndex;
	vec3ui	textureIndex;
	vec3ui	normalIndex;
};