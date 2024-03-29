#version 330

in vec2 f_uvcoords;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main(void)
{
    float alpha = texture(ourTexture, f_uvcoords).a;

    if (alpha < 0.5)
    {
        discard;
    }

    FragColor = vec4(1.0);
}