#version 440 core

in vec2 f_texcoord;

out vec4 fragColor;

uniform sampler2D ourTexture;
uniform vec3 color = vec3(0.8, 0.8, 0.2); // #TODO

void main()
{
    float alpha = texture(ourTexture, f_texcoord).r;
    if (alpha < 0.1)
        discard;

    fragColor = vec4(color, alpha);
}
