#include "scop.hpp"

mat4x4 _createTransformationMat(
	const vec3<float> &translation, const vec3<float>rotation)
{
	mat4x4 res;

	
	mat4x4 scale_matrix;
	mat4x4 translation_matrix;
	mat4x4 rotation_matrix;
	
	mat4x4 rotation_x_matrix;
	mat4x4 rotation_y_matrix;
	mat4x4 rotation_z_matrix;
	
	translation_matrix = MAT4X4_TRANSLATION(translation);
	scale_matrix = MAT4X4_UNIFORM_SCALE(1);
	rotation_x_matrix = MAT4X4_ROTATION_X(rotation.x);
	rotation_y_matrix = MAT4X4_ROTATION_Y(rotation.y);
	rotation_z_matrix = MAT4X4_ROTATION_Z(rotation.z);
	rotation_matrix = rotation_z_matrix * rotation_y_matrix * rotation_x_matrix;
	res = translation_matrix * rotation_matrix * scale_matrix;

	return (res);
}

mat4x4 _createProjectionMat()
{
	mat4x4 res = MAT4X4(0);

	const float fov = FOV * M_PI / 180.0f;
	const float ratio = WIDTH / HEIGTH;
	res.mat[0][0] = (1 / (ratio * tan(fov / 2)));
	res.mat[1][1] = (1 / (tan(fov/2)));
	res.mat[2][2] = -((ZFAR + ZNEAR) / (ZFAR - ZNEAR));
	res.mat[2][3] = -((2 * ZFAR * ZNEAR) / (ZFAR - ZNEAR));
	res.mat[3][2] = -1;

	return (res);
}