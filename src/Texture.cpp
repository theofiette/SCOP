
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data);

	glGenerateMipmap(GL_TEXTURE_2D);

	if (texture.data)
		delete texture.data;

	std::cout
		<< "Default constructor called for class Texture" << std::endl;
}

   		// char  idLength;
   		// char  colourMapType;
   		// char  dataTypeCode;
   		// u_int16_t colourMapOrigin;
   		// u_int16_t colourMapLength;
   		// char  colourMapDepth;
   		// u_int16_t xOrigin;
   		// u_int16_t yOrigin;
   		// u_int16_t width;
   		// u_int16_t height;
   		// char  bitsPerPixel;
   		// char  imageDescriptor;

void printTgaHeader(t_tgaHeader *header)
{
    printf("idLength: %d\n", (unsigned char)header->idLength);
    printf("colourMapType: %d\n", (unsigned char)header->colourMapType);
    printf("dataTypeCode: %d\n", (unsigned char)header->dataTypeCode);
    printf("colourMapOrigin: %u\n", header->colourMapOrigin);
    printf("colourMapLength: %u\n", header->colourMapLength);
    printf("colourMapDepth: %d\n", (unsigned char)header->colourMapDepth);
    printf("xOrigin: %u\n", header->xOrigin);
    printf("yOrigin: %u\n", header->yOrigin);
    printf("width: %u\n", header->width);
    printf("height: %u\n", header->height);
    printf("bitsPerPixel: %d\n", (unsigned char)header->bitsPerPixel);
    printf("imageDescriptor: %d\n", (unsigned char)header->imageDescriptor);
}

void Texture::_parseTga(const char *content, textureData &texture) const
{

	tgaHeader		header = *(reinterpret_cast<const tgaHeader *>(content));
	unsigned int	textureSize;
	unsigned int	incomingChannelsNumber;

	// Checking that the texture file has 3 or 4 channels
	incomingChannelsNumber = header.bitsPerPixel / 8;
	if (incomingChannelsNumber != 3 && incomingChannelsNumber != 4)
	{
		std::cout << "ERROR::TEXTURE::INVALID_CHANNELS_NUMBER" << std::endl;
		clean_exit(true, 1);
	}

	printTgaHeader(&header);

	texture.height =			header.height;
	texture.width =				header.width;
	texture.channelsNumber =	4; // RGBA

	textureSize = header.height * header.width * texture.channelsNumber;
	texture.data = new unsigned char[textureSize]; // outFormat is RGBA

	std::cout << "texture incomming channels is : " << incomingChannelsNumber << std::endl;

	unsigned int j = 0; // Current channel pixel in the incomming file
	unsigned int current_texture_channel;

	(void)current_texture_channel;

	// For each channel in the texture
	for (unsigned int i = 0; i < textureSize; i ++)
	{
		switch (i % texture.channelsNumber) // RGBA
		{
			case 0 :
				texture.data[i] = content[ sizeof(tgaHeader) + j + 2];
				j ++;
				break ;
			
			case 1 :
				texture.data[i] = content[ sizeof(tgaHeader) + j];
				j++;
				break ;

			case 2 :
				texture.data[i] = content[ sizeof(tgaHeader) + j - 2];
				j++;
				break ;

			case 3 :
				if (incomingChannelsNumber == 4) // inFormat is RGBA
				{
					texture.data[i] = content[ sizeof(tgaHeader) + j];
					j++;
				}
				else if (incomingChannelsNumber == 3) // inFormat is RGB
					texture.data[i] = 255; // NO ALPHA
				break ;

		}
	}

}

textureData		Texture::_loadTexture(const char* path) const
{

	textureData		texture;
	std::string		extension;
	std::string		textureContent;

	extension = FileLoader::getExtension(path);
	textureContent = FileLoader::toString(path);

	if (extension == ".tga") {

		_parseTga(textureContent.c_str(), texture);

	}

	return (texture);
}


// Texture::Texture(const Texture &other) : _ID(other.getID())
// {
// 	std::cout
// 		<< "Copy constructor called for class Texture" << std::endl;
// };

// ASSIGNEMENT OPERATOR

// Texture &Texture::operator=(const Texture &other)
// {
// 	if (this != &other)
// 	{
// 		_ID = other.getID();
// 	}
// 	std::cout
// 		<< "Copy assignment operator called for class Texture" << std::endl;
// 	return (*this);
// }

// DESTRUCTOR

Texture::~Texture()
{
	// TODO : glDeleteTextures ?
	std::cout
		<< "Destructor called for class Texture" << std::endl;
}
