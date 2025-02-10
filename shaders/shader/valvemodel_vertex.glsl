#version 430 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uvcoord;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in int v_boneid;
layout (location = 4) in int v_textureid;

out vec2 f_uvcoord;
flat out int f_textureid;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
uniform mat4 bonesMat[64];
//uniform float clipplane;


void main(void)
{
	vec4 worldPos = modelMat * bonesMat[v_boneid] * vec4(v_position, 1.0f);
	// vec4 worldPos = modelMat * vec4(v_position, 1.0f);

	// gl_ClipDistance[0] = dot(worldPos, vec4(0,clipplane,0,0));
	gl_Position = projMat * viewMat * worldPos;

    f_uvcoord = v_uvcoord;
    f_textureid = v_textureid;
}