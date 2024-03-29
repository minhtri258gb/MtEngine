#version 430 core

in vec2 f_uvcoord;

out vec4 FragColor;

uniform sampler2D lineTexture;
uniform vec3 lineColor;


void main(void)
{
    FragColor = vec4(lineColor, texture(lineTexture, f_uvcoord).a);
}
