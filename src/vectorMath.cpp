#include "vectorMath.hpp"

namespace vectorMath {

	vec3<float> normalize(const vec3<float> &vec)
	{
		float len = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

		if (!len)
			return (vec3<float>(0.0f, 0.0f, 0.0f));
		return (vec / len);
	}

	vec3<float> cross(const vec3<float> &a, const vec3<float> &b)
	{
		return (vec3<float>(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		));
	}
}
