#version 330 core

in vec2 uvcoord;

out vec4 FragColor;

uniform sampler2D ourTexture;


vec3 textureColour()
{
    return texture(ourTexture, uvcoord).xyz;
}

vec3 kernel_effect(float kernel[9])
{
    const float offset = 1.0 / 300.0;

    vec2 offsets[9] = vec2[] (
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

    vec3 sampleTex[9];
    for (int i=0; i<9; i++)
        sampleTex[i] = vec3(texture(ourTexture, uvcoord.st + offsets[i]));

    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return col;
}

vec3 effect1()
{
    float kernel[9] = float[] (2,2,2,2,-15,2,2,2,2);
    return kernel_effect(kernel);
}

vec3 effect2()
{
    float kernel[9] = float[] (-1,-1,-1,-1,9,-1,-1,-1,-1);
    return kernel_effect(kernel);
}

vec3 effect_blur()
{
    float kernel[9] = float[] (1.0/16,2.0/16,1.0/16,2.0/16,4.0/16,2.0/16,1.0/16,2.0/16,1.0/16);
    return kernel_effect(kernel);
}

vec3 effect_edge()
{
    float kernel[9] = float[] (1,1,1,1,8,1,1,1,1);
    return kernel_effect(kernel);
}

vec3 inversion(vec3 colour)
{
    return 1.0 - colour;
}

vec3 grayscale(vec3 colour)
{
    float avg = (colour.r + colour.g + colour.b) / 3.0;
    return vec3(avg);
}

vec4 result(vec3 colour)
{
    return vec4(colour, 1.0);
}

void main(void)
{
    vec3 colour = textureColour();
    // vec3 colour = effect1();
    // vec3 colour = effect2();
    // vec3 colour = effect_blur();
    // vec3 colour = effect_edge();

    // colour = grayscale(colour);
    // colour = inversion(colour);

    //FragColor = result(vec3(colour.r,colour.r,colour.r));
    FragColor = result(colour);
}
