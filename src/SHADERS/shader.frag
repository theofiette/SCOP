#version 440 core

in vec2 texCoord;
in vec3 vertexColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

out vec4 FragColor;

void main()
{
	FragColor = texture(tex2, texCoord);
}