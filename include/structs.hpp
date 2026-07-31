#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct vec2 {
	float	x;
	float	y;
};

struct vec3 {
    float	x;
    float	y;
    float	z;
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
};

struct vec4ui {
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
	unsigned int	a;
};

struct Vertex {
    vec3	position;
    vec2 	normal;
    vec2 	texCoord;
	vec3	color;
};

struct FaceIndexes {
	vec3ui	positionIndex;
	vec3ui	normaleIndex;
	vec3ui	textureIndex;
};