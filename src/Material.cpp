
#include "Material.hpp"

// CONSTRUCTORS

//TODO: Could get the texture directly via parsing the .mtl
Material::Material(const char *texturePath) :
_texture(texturePath, true),
_textureShader(TEXTURE_SHADER_VERT, TEXTURE_SHADER_FRAG),
_colorShader(COLOR_SHADER_VERT, COLOR_SHADER_FRAG)
{
	_texture.bind(0);
	_textureShader.setUniform<int>("tex", 0);
}

Texture &Material::getTexture()
{
	return (_texture);
}

Shader	&Material::getTextureShader()
{
	return (_textureShader);
}

Shader	&Material::getColorShader()
{
	return (_colorShader);
}

// DESTRUCTOR

Material::~Material()
{
}
