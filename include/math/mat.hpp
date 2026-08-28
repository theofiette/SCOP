# pragma once 

# include <stdexcept>

typedef union mat4x4 {

	struct {

		float _00, _01, _02, _03;
		float _10, _11, _12, _13;
		float _20, _21, _22, _23;
		float _30, _31, _32, _33;

	};
	struct {

		float	m[16];
		
	};
	struct {
		float   mat[4][4];
	};

	mat4x4	&operator*(mat4x4 &other) {
		
		// safety check 

		mat4x4	retval = {};

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
					retval.mat[i][j] += mat[i][k] * other.mat[k][j];
				
			}
		}

		*this = retval;
		return (*this);
	}

} mat4x4;

# define MAT4X4(x)	mat4x4 {	x, x, x, x, \
								x, x, x, x, \
								x, x, x, x, \
								x, x, x, x}

# define MAT4X4_IDENTITY	mat4x4 {	1, 0, 0, 0, \
										0, 1, 0, 0, \
										0, 0, 1, 0, \
										0, 0, 0, 1}

# define MAT4X4_UNIFORM_SCALE(x)	mat4x4 {	x, 0, 0, 0, \
												0, x, 0, 0, \
												0, 0, x, 0, \
												0, 0, 0, 1	}

# define MAT4X4_SCALE(vec3)			mat4x4 {	vec3.x, 0, 0, 0, \
												0, vec3.y, 0, 0, \
												0, 0, vec3.z, 0, \
												0, 0, 0, 1	}											

# define MAT4X4_TRANSLATION(vec3)	mat4x4 {	1, 0, 0, vec3.x, \
												0, 1, 0, vec3.y, \
												0, 0, 1, vec3.z, \
												0, 0, 0, 1	}

# define MAT4X4_ROTATION_X(angle)	mat4x4 {	1, 0, 0, 0, \
												0, cosf(angle), -sinf(angle), 0, \
												0, sinf(angle), cosf(angle), 0, \
											 	0, 0, 0, 1	}

# define MAT4X4_ROTATION_Y(angle)	mat4x4 {	cosf(angle), 0, sinf(angle), 0, \
												0, 1, 0, 0, \
												-sinf(angle), 0, cosf(angle), 0, \
												0, 0, 0, 1	}

# define MAT4X4_ROTATION_Z(angle)	mat4x4 {	cosf(angle), -sinf(angle), 0, 0, \
												sinf(angle), cosf(angle), 0, 0, \
												0, 0, 1, 0, \
												0, 0, 0, 1	}
