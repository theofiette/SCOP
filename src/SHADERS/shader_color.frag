#version 440 core

flat in vec3 fragColor;

out vec4 FragColor;

void main()
{
	FragColor = vec4(fragColor.x, fragColor.y, fragColor.z, 1.0);
}