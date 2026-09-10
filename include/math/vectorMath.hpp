#pragma once

# include <cmath>
# include "core/define.hpp"
# include "math/vec.hpp"

namespace vectorMath {

	vec3<float> normalize(const vec3<float> &vec);

	vec3<float> cross(const vec3<float> &a, const vec3<float> &b);

}


