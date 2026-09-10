
#include "render/Camera.hpp"

void	Camera::_setProjectionMatrix()
{
	_projection = MAT4X4(0);

	const float fov = FOV * M_PI / 180.0f;
	const float ratio = WIDTH / HEIGHT;
	_projection.mat[0][0] = (1 / (ratio * tan(fov / 2)));
	_projection.mat[1][1] = (1 / (tan(fov/2)));
	_projection.mat[2][2] = -((ZFAR + ZNEAR) / (ZFAR - ZNEAR));
	_projection.mat[2][3] = -((2 * ZFAR * ZNEAR) / (ZFAR - ZNEAR));
	_projection.mat[3][2] = -1;

}

const mat4x4	&Camera::getProjectionMatrix() const
{
	return (_projection);
}

// CONSTRUCTORS

Camera::Camera()
{
	_setProjectionMatrix();
}

Camera::Camera(const Camera &other)
{
	_projection = other._projection;
};

// ASSIGNEMENT OPERATOR

Camera &Camera::operator=(const Camera &other)
{
	_projection = other._projection;
	return (*this);
}

// DESTRUCTOR

Camera::~Camera()
{

}
