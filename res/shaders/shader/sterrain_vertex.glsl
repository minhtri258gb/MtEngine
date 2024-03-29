#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uvOvercoord;

out vec2 f_uvOvercoord;
out vec2 f_uvTilecoord;
out vec4 f_shadowCoord;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 shadowSpace;


void main(void)
{
	vec4 worldPos = vec4(v_position, 1.0);
	vec4 posRelToCam = viewMat * worldPos;

	gl_ClipDistance[0] = dot(worldPos, vec4(0,-1,0,0));
	gl_Position = projMat * posRelToCam;

	f_uvOvercoord = v_uvOvercoord;
	f_uvTilecoord = worldPos.xz / 512.0;
	f_shadowCoord = shadowSpace * worldPos;
}
