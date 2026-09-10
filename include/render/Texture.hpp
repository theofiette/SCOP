# pragma once

# include <iostream>

# include "core/opengl.hpp"
# include "core/define.hpp"
# include "core/prototype.hpp"

// Could add inFormat and outFormat to deal with RGBA
typedef struct textureData {

	unsigned char	*data = NULL;
	unsigned int	width;
	unsigned int	height;
	unsigned int	inFormat;
	unsigned int	outFormat;

} t_textureData;

typedef   struct __attribute__ ((packed)) tgaHeader {

   		char 		idLength;
   		char  		colourMapType;
   		char  		dataTypeCode;
   		u_int16_t	colourMapOrigin;
   		u_int16_t	colourMapLength;
   		char 		colourMapDepth;
   		u_int16_t	xOrigin;
   		u_int16_t	yOrigin;
   		u_int16_t	width;
   		u_int16_t	height;
   		char		bitsPerPixel;
   		char		imageDescriptor;

}  t_tgaHeader;

class Texture
{
	private:

		unsigned int	_ID;

		textureData		_loadTexture(const char* path, bool flip) const;
		void			_parseTga(const char * content, textureData &texture, bool flip) const;
		void			_initTextureParameter();

		Texture() = delete;		//Default constructor is not allowed
		Texture(const Texture &other) = delete;	//Copy constructor is not allowed
		Texture	&operator=(const Texture &other) = delete; //Assignement operator is not allowed

	public:

		unsigned int	getID() const;
		void			bind(unsigned int textureUnit) const;

		// Orthodox Canonical Form
					Texture(const char* path, bool flip = false);
		virtual 	~Texture();						//Destructor
};
