#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct vec3 {
    float   x;
    float   y;
    float   z;
};

struct vec3i {
    int   x;
    int   y;
    int   z;
};

struct Vertex {
    vec3 position;
    vec3 normal;
    vec3 texCoord;
};