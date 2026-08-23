#ifndef SCOP_HPP
#define SCOP_HPP

# define WIDTH		1920.0f
# define HEIGTH 	1080.0f

# define FOV		90.0f
# define ZNEAR		0.1f
# define ZFAR		1000.0f

# define SENSIBILITY_MIN	0.1f
# define SENSIBILITY_MAX	1.0f
# define SENSIBILITY_STEP	0.1f
# define SENSIBILITY_BASE	1.0f

# define CHANNELS_IN_RGB 	3
# define CHANNELS_IN_RGBA	4

# define BASIC_TEXTURE_PATH	"resources/textures/dog.tga"
// # define BASIC_TEXTURE_PATH	"resources/textures/mire.tga"

// used for better hash scattering
# define GOLDEN_RATIO	0x9e3779b9

// OpenGL
# include <glad/glad.h>
# include <GLFW/glfw3.h>

// Basics
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <string.h>
# include <unordered_map>

# include <algorithm>

// fileLoader
# include "fileLoader.hpp"

// Structs
# include "structs.hpp"

// Classes
# include "Mesh.hpp"
# include "Shader.hpp"
# include "Texture.hpp"

// Math
# include <cmath>

// Prototypes

int		clean_exit(bool should_glfwTerminate, int exit_code);

void 	init(GLFWwindow** window_ptr);

void	_onWindowResize(GLFWwindow* window, int width, int height);
void	_onScroll(GLFWwindow* window, double x, double y);
void	_processInputs(GLFWwindow* window, vec3<float> &translation, vec3<float> &rotation);

mat4x4 _createTransformationMat(const vec3<float> &translation, const vec3<float>rotation);
mat4x4 _createProjectionMat();

#endif