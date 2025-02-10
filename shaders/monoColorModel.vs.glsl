#version 330 core

layout (location = 0) in vec3 v_position;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main(void)
{
	gl_Position = proj * view * model * vec4(v_position, 1.0);
}
