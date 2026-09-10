# pragma once

# include "core/define.hpp"
# include "math/vec.hpp"

struct Vertex {

	vec3<float>	position;
	vec2<float>	texture;
	vec3<float>	normal;
	vec3<float>	color;
	vec3<float>	normalColor;

	bool operator==(const Vertex &other) const {
		return (
			position == other.position &&
			texture == other.texture &&
			normal == other.normal &&
			color == other.color &&
			normalColor == other.normalColor
		);}
};

// ------------------------------------------------------------

// This part of the code has been generated with IA and reworked :
// Used to enable unordered map hash table

static std::size_t hashCombine(std::size_t h, std::size_t next)
{
	return (h ^ (next + GOLDEN_RATIO + (h << 6) + (h >> 2)));
}

struct VertexHash
{
	std::size_t operator()(const Vertex &v) const
	{
		std::size_t h;
		
		h =	std::hash<float>()(v.position.x);
		h =	hashCombine(h, std::hash<float>()(v.position.y));
		h = hashCombine(h, std::hash<float>()(v.position.z));
		h = hashCombine(h, std::hash<float>()(v.texture.x));
		h = hashCombine(h, std::hash<float>()(v.texture.y));
		h = hashCombine(h, std::hash<float>()(v.normal.x));
		h = hashCombine(h, std::hash<float>()(v.normal.y));
		h = hashCombine(h, std::hash<float>()(v.normal.z));
		h = hashCombine(h, std::hash<float>()(v.color.x));
		h = hashCombine(h, std::hash<float>()(v.color.y));
		h = hashCombine(h, std::hash<float>()(v.color.z));

		return h;
	}
};

//-------------------------------------------------------------