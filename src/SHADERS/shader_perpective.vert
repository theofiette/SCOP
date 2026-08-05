#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec2 aNormal;
layout (location = 3) in vec3 aColor;

uniform float offset;
uniform float tanhalffov;

flat out vec3 fragColor;

uniform mat4 projection;

void main()
{
	vec3 pos = aPos;
	pos.y -= 2.0f;
	pos.z -= 3.0f;
	gl_Position = projection * vec4(pos, 1.0);
	fragColor = aColor;
}