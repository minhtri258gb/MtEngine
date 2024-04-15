#version 440 core

layout (location = 0) in vec3 v_position;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;


void main()
{
	vec3 f_trans_position = vec3(model * vec4(v_position, 1.0f));
	gl_Position = proj * view * vec4(f_trans_position, 1.0f);
}
