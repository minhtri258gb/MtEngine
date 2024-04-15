#version 440 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in int v_level;
layout (location = 2) in int v_flag;

out vec2 c_position;
out vec2 c_texcoord;
out int c_level;
out int c_flag;

uniform float cellSpace = 1; // #TODO
uniform ivec2 location = ivec2(0.0, 0.0); // #TODO


void main()
{
	// Data
	float size = float(1 << v_level);
	const vec2 vertices[] = vec2[] (vec2(0, 0), vec2(0, size), vec2(size, 0), vec2(size, size));

	// Position
	c_position = (v_position + vertices[gl_VertexID] + location * 256.0) * cellSpace;

	// Texture
	c_texcoord = vec2(c_position.x / 256.0, c_position.y / 256.0);
	c_level = v_level;
	c_flag = v_flag;
}
