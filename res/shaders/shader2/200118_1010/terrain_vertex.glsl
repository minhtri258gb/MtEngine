#version 430 core

layout (location = 0 ) in vec2 v_position;
//layout (location = 1 ) in vec2 v_uvoord;

//out vec2 tc_position;
//out vec2 tc_uvOvercoord;

uniform mat4 projection;
uniform mat4 view;

const float terrainSize = 8192.0;


void main(void)
{
    gl_Position = projection * view * vec4(v_position.x * terrainSize, 50.0, v_position.y * terrainSize, 1.0);

	//tc_uvOvercoord = v_position;
	//tc_position = v_position * terrainSize;
}
