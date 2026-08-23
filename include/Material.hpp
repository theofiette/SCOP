# pragma once

# include "Texture.hpp"
# include "Shader.hpp"

class Material
{

	private:

		Texture		_texture;
		Shader		_textureShader;
		Shader		_colorShader;		

		// Deleted functions --------------------------------------

					Material() 							= delete;
		Material	&operator=(const Material &other)	= delete;
					Material(const Material &other)		= delete;

		// --------------------------------------------------------

	public:

		Texture		&getTexture();
		Shader		&getTextureShader();
		Shader		&getColorShader();

					Material(const char *texturePath);
		virtual 	~Material();
};
		
