
#include "Texture.hpp"

unsigned int	Texture::getID() const
{
	return (_ID);
}

void			Texture::bind(unsigned int textureUnit) const
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, _ID);
}

// CONSTRUCTORS

Texture::Texture(const char* path, bool flip)
{
	t_textureData texture;
	
	texture = _loadTexture(path);

	(void)flip;

	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);


	std::cout
		<< "Default constructor called for class Texture" << std::endl;
}

textureData		Texture::_loadTexture(const char* path) const
{

	t_textureData	texture;
	std::string		extension;
	std::string		textureContent;

	extension = FileLoader::getExtension(path);

	std::cout << "File extension is : " << extension << std::endl;
	
	textureContent = FileLoader::toString(path);

	return (texture);
}


Texture::Texture(const Texture &other) : _ID(other.getID())
{
	std::cout
		<< "Copy constructor called for class Texture" << std::endl;
};

// ASSIGNEMENT OPERATOR

Texture &Texture::operator=(const Texture &other)
{
	if (this != &other)
	{
		_ID = other.getID();
	}
	std::cout
		<< "Copy assignment operator called for class Texture" << std::endl;
	return (*this);
}

// DESTRUCTOR

Texture::~Texture()
{
	// TODO : glDeleteTextures ?
	std::cout
		<< "Destructor called for class Texture" << std::endl;
}
