#ifndef SCOP_HPP
#define SCOP_HPP

# include "define.hpp"

// OpenGL
# include "opengl.hpp"

// Basics and containers
# include <unistd.h>
# include <stdio.h>
# include <cstdlib>
# include <iostream>
# include <string.h>
# include <unordered_map>

// Math & algo
# include <algorithm>
# include <cmath>

// Classes
# include "classes.hpp"

// Prototypes
# include "prototype.hpp"

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

#endif