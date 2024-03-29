#version 330 core

in vec2 pass_textureCoord;
in vec3 pass_normal;

out vec4 out_Color;

uniform sampler2D ourTexture;

void main(void)
{
    out_Color = texture(ourTexture, pass_textureCoord);
}