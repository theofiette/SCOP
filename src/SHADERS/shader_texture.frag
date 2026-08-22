#version 440 core

in vec3 fragColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	FragColor = texture(tex, texCoord);
}