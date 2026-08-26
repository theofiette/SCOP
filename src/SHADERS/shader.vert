#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec2 aNormal;
layout (location = 3) in vec3 aColor;
layout (location = 4) in vec3 aNormalColor;

uniform mat4 projection;
uniform mat4 transformation;
uniform float normalDisplay;

flat out vec4 fragColor;
out vec2 texCoord;

void main()
{
	gl_Position = projection * transformation * vec4(aPos, 1.0);
	fragColor = mix(vec4(aColor, 1), vec4(aNormalColor, 1), normalDisplay);
	texCoord = aTexture;
}
