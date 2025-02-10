#version 330 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in mat4 v_viewmodel;
layout (location = 5) in vec4 v_texoffset;
layout (location = 6) in float v_blend;

out vec4 f_uvcoord;
out float f_blend;

uniform mat4 projection;
uniform int numOfRows;


void main(void)
{
    gl_Position = projection * v_viewmodel * vec4(v_position, 0.0, 1.0);

    vec2 texcoord = v_position + vec2(0.5, 0.5);
    texcoord.y = 1.0 - texcoord.y;
    texcoord /= numOfRows;
    f_uvcoord.xy = texcoord + v_texoffset.xy;
    f_uvcoord.zw = texcoord + v_texoffset.zw;

    f_blend = v_blend;
}
