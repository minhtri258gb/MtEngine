#version 330 core

in vec2 f_uvcoord;

out vec4 FragColor;

uniform sampler2D grassTex;


void main(void)
{
	FragColor = texture(grassTex, f_uvcoord);
	if (FragColor.a < 0.5)
		discard;
}
