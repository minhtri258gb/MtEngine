#version 330 core

in vec4 position;

out vec2 uvcoord;

uniform mat4 projection;


void main(void)
{
	gl_Position = projection * vec4(position.xy, 0.0, 1.0);

	uvcoord = position.zw;
}
