# pragma once

# include <stdexcept>
# include <ostream>

template <typename T>
struct vec2 {
	T	x;
	T	y;

	vec2() : x{0}, y{0} {};
	vec2(T _x, T _y) : x{_x}, y{_y} {};

	bool operator==(const vec2 &other) const {
		return (
		x == other.x &&
		y == other.y
	);}

	T &operator[](unsigned int index) {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			default:
				throw (std::out_of_range("vec2 invalid index"));
		}
	}

	T operator[](unsigned int index) const {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			default:
				throw (std::out_of_range("vec2 invalid index"));
		}
	}
};

template <typename T> 
struct vec3 
{
	T	x;
	T	y;
	T	z;

	vec3() : x{0}, y{0}, z{0} {};

	vec3(T value) : x{value}, y{value}, z{value} {};

	vec3(T _x, T _y, T _z) : x{_x}, y{_y}, z{_z} {};

	vec3	operator/(const float unit) const {
		return (vec3(x / unit, y / unit, z / unit));
	}

	vec3	operator-(const vec3 &other) const {
		return (vec3(x - other.x, y - other.y, z - other.z));
	}

	vec3	&operator-=(const vec3 &other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return (*this);
	}

	bool operator==(const vec3 &other) const {
		return (
			x == other.x &&
			y == other.y &&
			z == other.z
	);}

	T &operator[](unsigned int index) {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			case (2):
				return (z);
			default:
				throw (std::out_of_range("vec3 invalid index"));
		}
	}

	T operator[](unsigned int index) const {
		switch (index) {
			case (0):
				return (x);
			case (1):
				return (y);
			case (2):
				return (z);
			default:
				throw (std::out_of_range("vec3 invalid index"));
		}
	}

	friend std::ostream &operator<<(std::ostream &os, vec3 &vec) {
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return (os);
	}

	T	max() {
		if (x >= y && x >= z)
			return (x);
		if (y >= x && y >= z)
			return (y);
		else
			return (z);
	}

	T	min() {
		if (x <= y && x <= z)
			return (x);
		if (y <= x && y <= z)
			return (y);
		else
			return (z);
	}

	vec3	abs()
	{
		return (vec3<T>(
			(x < 0 ? -x : x),
			(y < 0 ? -y : y),
			(z < 0 ? -z : z))
		);
	}
};