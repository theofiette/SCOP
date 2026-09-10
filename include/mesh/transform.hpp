# pragma once

# include "math/vec.hpp"

struct Transform {
	vec3<float> translation;
	vec3<float>	rotation;
	vec3<float> scale;

	Transform(vec3<float> pos, vec3<float> rot, vec3<float> sca) : 
	translation(pos), rotation(rot), scale(sca) {};

	Transform() {};
};