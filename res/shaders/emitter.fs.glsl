#version 440 core

in vec4 f_texcoord;
in float f_blend;

out vec4 fragColor;

uniform sampler2D ourTexture;


void main(void)
{
    vec4 colour1 = texture(ourTexture, f_texcoord.xy);
    vec4 colour2 = texture(ourTexture, f_texcoord.zw);
    if (colour1.a + colour1.a < 0.01)
        discard;

    fragColor = mix(colour1, colour2, f_blend);
}
