#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uvcoord;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in int v_boneid;
layout (location = 4) in int v_mtlid;

out vec2 f_uvcoord;
flat out int f_mtlid;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 bones[64];
uniform float clipplane;


void main(void)
{
	vec4 worldPos = model * bones[v_boneid] * vec4(v_position, 1.0f);

	gl_ClipDistance[0] = dot(worldPos, vec4(0,clipplane,0,0));
	gl_Position = proj * view * worldPos;

    f_uvcoord = v_uvcoord;
    f_mtlid = v_mtlid;
}