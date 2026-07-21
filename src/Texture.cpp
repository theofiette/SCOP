
#include "Texture.hpp"

// CONSTRUCTORS

Texture::Texture()
{
	std::cout
		<< "Default constructor called for class Texture" << std::endl;
}

Texture::Texture(const Texture &other)
{
	std::cout
		<< "Copy constructor called for class Texture" << std::endl;
};

// ASSIGNEMENT OPERATOR

Texture &Texture::operator=(const Texture &other)
{
	std::cout
		<< "Copy assignment operator called for class Texture" << std::endl;
	return (*this);
}

// DESTRUCTOR

Texture::~Texture()
{
	std::cout
		<< "Destructor called for class Texture" << std::endl;
}
