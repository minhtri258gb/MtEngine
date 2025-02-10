#version 330 core

in vec2 uvcoord;

out vec4 FragColor;

uniform sampler2D hudTexture;
uniform float visiable;


void main(void)
{
	vec4 textureColor = texture(hudTexture, uvcoord);
	textureColor.a *= visiable;
	if (textureColor.a == 0.0)
		discard;
    FragColor = textureColor;
}
