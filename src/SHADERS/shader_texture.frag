#version 440 core

in vec3 fragColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	vec4 color;
	color = vec4(fragColor.x, fragColor.y, fragColor.z, 1.0);
	FragColor = mix(color, texture(tex, texCoord), 0.5);
	FragColor = texture(tex, texCoord);
}