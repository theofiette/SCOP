#ifndef SCOP_HPP
#define SCOP_HPP

# define WIDTH		1920.0f
# define HEIGTH 	1080.0f

# define FOV		60.0f
# define ZNEAR		0.1f
# define ZFAR		1000.0f

# define SENSIBILITY_MIN	0.1f
# define SENSIBILITY_MAX	1.0f
# define SENSIBILITY_STEP	0.1f
# define SENSI_BASE	1.0f

# define CHANNELS_IN_RGB 	3
# define CHANNELS_IN_RGBA	4

# define TEXTURE_SHADER_VERT	"src/SHADERS/shader_texture.vert"
# define TEXTURE_SHADER_FRAG	"src/SHADERS/shader_texture.frag"
# define COLOR_SHADER_VERT		"src/SHADERS/shader_color.vert"
# define COLOR_SHADER_FRAG		"src/SHADERS/shader_color.frag"
# define BASIC_TEXTURE_PATH		"resources/textures/dog.tga"

// used for better hash scattering
# define GOLDEN_RATIO	0x9e3779b9

// OpenGL
# include "opengl.hpp"

// Basics and containers
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <string.h>
# include <unordered_map>

// Math & algo
# include <algorithm>
# include <cmath>

// Structs
# include "structs.hpp"

// // Classes
// # include "classes.hpp"

// Prototypes

int		clean_exit(bool should_glfwTerminate, int exit_code);

void 	init(GLFWwindow** window_ptr, registre *registrePtr);

void	_onWindowResize(GLFWwindow* window, int width, int height);
void	_onScroll(GLFWwindow* window, double x, double y);
void	_processInputs(GLFWwindow* window, Transform &transform);

mat4x4 _createTransformationMat(const Transform &transform);
mat4x4 _createProjectionMat();
// void _processRender(GLFWwindow* window, mat4x4 &projection, Mesh &mesh, registre &registre, Material &material)

#endif