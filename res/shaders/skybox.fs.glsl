#version 430 core

in vec3 f_texcoord;

out vec4 fragColor;

uniform samplerCube ourTexture;

void main()
{
	fragColor = texture(ourTexture, f_texcoord);
	// fragColor = vec4(0.1, 0.1, 0.1, 1.0);
}
