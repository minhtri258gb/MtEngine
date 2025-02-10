#version 430 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in float v_scale;
layout (location = 2) in float v_process;
// layout (location = 1) in mat4 v_viewmodel;
// layout (location = 5) in vec4 v_texoffset;
// layout (location = 6) in float v_blend;

out float g_scale;
out float g_process;
// out vec4 f_uvcoord;
// out float f_blend;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
// uniform int numOfRows;


void main(void)
{
    vec4 worldPos = modelMat * vec4(v_position, 1.0);
    gl_Position = projMat * viewMat * worldPos;

    // vec4 worldPos = vec4(v_position, 0.0, 1.0);
    // gl_Position = projMat * v_viewmodel * worldPos;
    // gl_Position = projMat * v_viewmodel * vec4(v_position, 0.0, 1.0);

    g_scale = v_scale;
    g_process = v_process;

    // vec2 texcoord = v_position + vec2(0.5, 0.5);
    // texcoord.y = 1.0 - texcoord.y;
    // texcoord /= numOfRows;
    // f_uvcoord.xy = texcoord + v_texoffset.xy;
    // f_uvcoord.zw = texcoord + v_texoffset.zw;

    // f_blend = v_blend;
}
