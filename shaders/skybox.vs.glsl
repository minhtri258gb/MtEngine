#version 440 core

layout (location = 0) in vec3 v_position;

out vec3 f_texcoord;

uniform mat4 proj;
uniform mat4 view;

void main()
{
	f_texcoord = v_position;

	gl_Position = proj * view * vec4(v_position, 1.0f);
}
