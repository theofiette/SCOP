# pragma once

# include "mesh/Vertex.hpp"

struct Face {

	Vertex a;
	Vertex b;
	Vertex c;

	Vertex	&operator[](int index) {
		switch (index) {
			case (0):
				return (a);
			case (1):
				return (b);
			case (2):
				return (c);
			default:
				throw (std::out_of_range("Face invalid index"));
		}
	}
};