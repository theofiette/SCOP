#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aNormal;
layout (location = 2) in vec2 atexture;
layout (location = 3) in vec3 aColor;

uniform float offset;
uniform float tanhalffov;

flat out vec3 fragColor;

void main()
{
	gl_Position = vec4(aPos.x * 1 / tanhalffov, -aPos.y * 1 / tanhalffov, (aPos.z + offset) * 0.00002, 1.0);
	fragColor = aColor;
}