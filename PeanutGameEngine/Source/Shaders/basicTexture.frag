#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixture;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	// texture2 (the smiley face) is mirrored in this example
	FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(1.0 - texCoord.x, texCoord.y)), mixture);
}