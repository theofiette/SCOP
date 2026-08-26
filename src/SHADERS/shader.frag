#version 440 core

flat in vec4 fragColor;
in vec2 texCoord;

out vec4 FragColor;

uniform float texCoef;
uniform sampler2D tex;

void main()
{
	FragColor = mix(texture(tex, texCoord), fragColor, texCoef);
}