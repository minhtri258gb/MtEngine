#version 440 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texcoord;
layout (location = 2) in vec3 v_normal;

out vec2 f_texcoord;
out vec3 f_normal;
out vec3 f_trans_position; // model * position

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;


void main()
{
	// Cal
	f_trans_position = vec3(model * vec4(v_position, 1.0f));

	// Pass
	f_texcoord = v_texcoord;
	f_normal = v_normal;

	// Main
	gl_Position = proj * view * vec4(f_trans_position, 1.0f);
}
