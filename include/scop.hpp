#ifndef SCOP_HPP
#define SCOP_HPP

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Structs
#include "structs.hpp"

// Classes
#include "FileLoader.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

// Math
#include <cmath>

// Prototypes

int clean_exit(bool should_glfwTerminate, int exit_code);

#endif