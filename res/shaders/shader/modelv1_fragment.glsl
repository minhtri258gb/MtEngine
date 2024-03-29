#version 330 core

in vec2 f_uvcoord;
flat in int f_mtlid;

out vec4 FragColor;

uniform sampler2D modelTexture[4];
uniform sampler2D shadowMap;


void main(void)
{
	FragColor = texture(modelTexture[f_mtlid], f_uvcoord);
}
