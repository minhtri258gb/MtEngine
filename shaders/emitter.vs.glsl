#version 440 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in float v_scale;
layout (location = 2) in float v_progress;

out float g_scale;
out float g_progress;


void main(void)
{
    // Pass
    g_scale = v_scale;
    g_progress = v_progress;

    // Main
	gl_Position = vec4(v_position, 1.0);
}
