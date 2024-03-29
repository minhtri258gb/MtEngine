#version 330 core

in vec3 f_uvoord;

out vec4 FragColor;

uniform samplerCube ourTexture;

void main(void)
{
    FragColor = texture(ourTexture, f_uvoord);
}