#version 430 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_offsetCell;
layout (location = 2) in int v_levelCell;
layout (location = 3) in int v_patchCell;

out vec2 tc_position;
out vec2 tc_uvOvercoord;
out vec2 tc_uvTilecoord;
out int tc_levelCell;
out int tc_patchCell;

uniform ivec2 nearzone;

void main(void)
{
	// pass
	tc_position = v_position * 32.0 * (1 << (v_levelCell)) + v_offsetCell;
	tc_uvOvercoord = tc_position / 8192.0 - nearzone;
	tc_levelCell = v_levelCell;
	tc_patchCell = v_patchCell;
}
