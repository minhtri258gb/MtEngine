#version 330 core

in vec2 uvcoord;

out vec4 out_Color;

uniform sampler2D ourTexture;
uniform vec3 color;


void main(void)
{
	vec4 textureColor = texture(ourTexture, uvcoord);
	if (textureColor.r < 0.5)
		discard;
	textureColor.xyz = color;
	out_Color = textureColor;
}
