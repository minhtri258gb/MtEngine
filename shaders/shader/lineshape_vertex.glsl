#version 430 core

layout (location = 0 ) in vec2 v_position;

uniform mat4 projMat;
uniform mat4 modelviewMat;


void main(void)
{
	gl_Position = projMat * modelviewMat * vec4(v_position.x, 0.0, v_position.y, 1.0);
}