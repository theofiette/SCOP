#version 440 core

in vec2 textureCoord;

uniform sampler2D tex;

out vec4 FragColor;

void main()
{
	FragColor = texture(tex, textureCoord);
}