# pragma once

# include <scop.hpp>

# include <iostream>

// Could add inFormat and outFormat to deal with RGBA
typedef struct textureData {

	unsigned char	*data;
	unsigned int	width;
	unsigned int	height;
	unsigned int	channelsNumber;

} t_textureData;

class Texture
{
	private:

		unsigned int	_ID;

		textureData			_loadTexture(const char* path) const;

		Texture(); 						//Default constructor is not allowed

	public:

		unsigned int	getID() const;
		void			bind(unsigned int textureUnit) const;

		// Orthodox Canonical Form
					Texture(const char* path, bool flip = false);
					Texture(const Texture &other);	//Copy constructor
		virtual 	~Texture();						//Destructor
		Texture	&operator=(const Texture &other); //Assignement operator
};
