#version 430 core

in vec4 f_uvcoord;
in float f_blend;

out vec4 Fragcolor;

uniform sampler2D particleTexture;


void main(void)
{
    vec4 colour1 = texture(particleTexture, f_uvcoord.xy);
    vec4 colour2 = texture(particleTexture, f_uvcoord.zw);
    Fragcolor = mix(colour1, colour2, f_blend);
    // Fragcolor = vec4(f_blend);
}
