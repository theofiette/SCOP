#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec2 aNormal;
layout (location = 3) in vec3 aColor;

uniform mat4 projection;

uniform mat4 scale;
uniform mat4 translate;
uniform mat4 rotate;

out vec3 fragColor;

void main()
{
	gl_Position = projection * translate * rotate * scale *  vec4(aPos, 1.0);
	fragColor = aColor;
}