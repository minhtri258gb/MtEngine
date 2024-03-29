#version 430 core

in vec2 f_uvoord;

out vec4 FragColor;

uniform sampler2D textureMain;


void main(void)
{
    FragColor = texture(textureMain, f_uvoord);
}