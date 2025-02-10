#version 330 core

in vec4 f_uvcoord;
in float f_blend;

out vec4 Fragcolour;

uniform sampler2D ourTexture;


void main(void)
{
    vec4 colour1 = texture(ourTexture, f_uvcoord.xy);
    vec4 colour2 = texture(ourTexture, f_uvcoord.zw);
    Fragcolour = mix(colour1, colour2, f_blend);
}
