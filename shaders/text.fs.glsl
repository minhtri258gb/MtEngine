#version 440 core

in vec2 f_texcoord;

out vec4 fragColor;

uniform sampler2D ourTexture;
uniform vec3 textColor;


void main(void)
{
	// vec4 textureColor = texture(ourTexture, f_texcoord);
	// if (textureColor.r < 0.5)
	// 	discard;
	// textureColor.xyz = textColor;
	// fragColor = textureColor;

	fragColor = vec4(1, 1, 1, 1);
}
