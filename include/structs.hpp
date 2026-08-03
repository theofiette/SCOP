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
};

struct vec3i {
    int	x;
    int	y;
    int	z;
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
		);}
};

struct vec4ui {
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
	unsigned int	a;
};

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