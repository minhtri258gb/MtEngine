#version 330 core

layout (location = 0) in vec3 v_position;

out vec2 f_uvcoord;
out vec4 f_shadowCoord;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 shadowSpace;

const float shadowDistance = 100.0;
const float transitionDistance = 10.0;


void main(void)
{
	vec4 worldPos = vec4(v_position, 1.0);
	vec4 posRelToCam = viewMat * worldPos;

	gl_ClipDistance[0] = dot(worldPos, vec4(0,0,-1,0));
	gl_Position = projMat * posRelToCam;

	f_uvcoord = worldPos.xy / 512.0;
	f_shadowCoord = shadowSpace * worldPos;
}
