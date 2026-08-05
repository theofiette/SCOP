#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec2 aNormal;
layout (location = 3) in vec3 aColor;

flat out vec3 fragColor;

uniform mat4 transformation;
uniform mat4 projection;

void main()
{
	gl_Position = transformation * vec4(aPos, 1.0);
	fragColor = aColor;
}