#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uvcoord;

out vec2 f_uvcoord;

uniform mat4 projMat;
uniform mat4 viewMat;


void main(void)
{
	vec4 worldPos = vec4(v_position, 1.0);

	worldPos.z += gl_InstanceID * 100.0;

	gl_Position = projMat * viewMat * worldPos;

	// pass
	f_uvcoord = v_uvcoord;
}
