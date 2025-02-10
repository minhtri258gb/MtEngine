#version 430 core

in vec2 f_uvcoord;
in vec3 f_normal;

out vec4 FragColor;

uniform sampler2D boxTexture;


void main(void)
{
    FragColor = texture(boxTexture, f_uvcoord);
}
