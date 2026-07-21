#version 440 core

in vec2 texCoord;
in vec3 vertexColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

out vec4 FragColor;

void main()
{
	FragColor = mix(texture(tex1, texCoord), texture(tex2, texCoord), 0.2);
}