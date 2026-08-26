
#include "Texture.hpp"
#include "fileLoader.hpp"

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
	
	texture = _loadTexture(path, flip);

	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data);

	glGenerateMipmap(GL_TEXTURE_2D);

	if (texture.data)
		delete texture.data;
	
	_initTextureParameter();
}

void _parseTgaHeader(const char *content, textureData &texture)
{
	tgaHeader		header = *(reinterpret_cast<const tgaHeader *>(content));

	// in and out channels
	texture.outFormat = 4; // Out as RGBA
	texture.inFormat = header.bitsPerPixel / 8;
	if (texture.inFormat != 3 && texture.inFormat != 4) // If not RGB neither RGBA
	{
		std::cout << "ERROR::TEXTURE::INVALID_CHANNELS_NUMBER" << std::endl;
		clean_exit(true, 7);
	}

	// dimensions
	texture.height	= header.height;
	texture.width	= header.width;
	texture.data	= new unsigned char[texture.height * texture.width * texture.outFormat];

}


/*
*	TODO : while this class is functionnal for the project, the tga parsing is not fully implemented
*/
void Texture::_parseTga(const char *content, textureData &texture, bool flip) const
{
	unsigned int inOffset = sizeof(tgaHeader);	// Reading bit from file
	unsigned int outOffset;						// Writing bit from texture
	unsigned int currentRow;					// Since the picture can be vertically flipped, it's not as simple as row ++
	int BGRtoRGB[3] = {2, 1, -0};				// To convert the byte order

	_parseTgaHeader(content, texture);

	for (unsigned int y = 0; y < texture.height; y ++)
	{
		currentRow = ( flip ? texture.height - y  - 1 : y);
		for (unsigned int x = 0; x < texture.width; x ++)
		{
			outOffset = currentRow * texture.width * texture.outFormat + x * texture.outFormat;

			for (unsigned int channel = 0; channel < CHANNELS_IN_RGB; channel ++)
				texture.data[outOffset + channel] = content[inOffset + BGRtoRGB[channel]];

			if (texture.inFormat == CHANNELS_IN_RGBA) // In is RGBA
				texture.data[outOffset + CHANNELS_IN_RGBA - 1] = content[inOffset + CHANNELS_IN_RGBA - 1];
			else if (texture.inFormat == CHANNELS_IN_RGB)
				texture.data[outOffset + CHANNELS_IN_RGBA - 1] = 255;
			inOffset += texture.inFormat;
		}	
	}
}

textureData		Texture::_loadTexture(const char* path, bool flip) const
{

	textureData		texture;
	std::string		extension;
	std::string		textureContent;

	extension = fileLoader::getExtension(path);
	textureContent = fileLoader::toString(path);

	if (extension == ".tga") {

		_parseTga(textureContent.c_str(), texture, flip);
	}
	else
	{
		clean_exit(true, 6);
	}

	return (texture);
}

void	Texture::_initTextureParameter()
{
	// texture repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

// DESTRUCTOR

Texture::~Texture()
{
	glDeleteTextures(1, &_ID);
}
