#version 440 core

layout (location = 0) in vec2 v_texcoord;
layout (location = 1) in vec2 v_position;

out vec2 f_texcoord;

uniform mat4 proj;


void main(void)
{
	// Pass
	f_texcoord = v_texcoord;

	// Main
	gl_Position = proj * vec4(v_position, 0.0, 1.0);
}
