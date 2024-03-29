#version 440 core

in vec2 f_texcoord;

out vec4 fragColor;

uniform sampler2D ourTexture;

void main()
{
	fragColor = texture(ourTexture, f_texcoord);
}
