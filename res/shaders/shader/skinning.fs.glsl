#version 440 core

in vec3 f_position;
in vec2 f_texcoord;
in vec3 f_normal;
in vec4 f_bw;

out vec4 color;

uniform sampler2D diff_texture;

vec3 lightPos = vec3(0.2, 1.0, -3.0);

void main()
{
    vec3 lightDir = normalize(lightPos - f_position);
    float diff = max(dot(f_normal, lightDir), 0.2);
    vec3 dCol = diff * texture(diff_texture, f_texcoord).rgb; 
    color = vec4(dCol, 1);
}
