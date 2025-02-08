#version 440 core

layout (vertices = 4) out;

in vec2 c_position[];
in vec2 c_texcoord[];
in int c_level[];
in int c_flag[];

out vec2 e_position[];
out vec2 e_texcoord[];

uniform sampler2D texHeight; // at TerrainPath
uniform float heightScale; // at TerrainPath
uniform vec3 camPos;


float getTessFactO(int id) {
	float fact = 4.0;
	if (id == 0 && (c_flag[0] & (1 << 0)) != 0)
		fact = fact / 2;
	if (id == 1 && (c_flag[1] & (1 << 1)) != 0)
		fact = fact / 2;
	if (id == 2 && (c_flag[2] & (1 << 2)) != 0)
		fact = fact / 2;
	if (id == 3 && (c_flag[3] & (1 << 3)) != 0)
		fact = fact / 2;
	return fact;
}

float getTessFactI(float dis) {
	if (c_level[0] == 1)
		return clamp((352 - dis) / 24, 4.0, 12.0); // ????
	else if (c_level[0] <= 7)
		return clamp(12 - dis/(1 << (4 + c_level[0])), 4.0, 8.0); // ????
	return 2.0;
}

void main() {

	if (gl_InvocationID == 0) {

		float height = texture(texHeight, c_texcoord[0]).r * heightScale;
		float dis = distance(camPos, vec3(c_position[gl_InvocationID].x, height, c_position[gl_InvocationID].y));

		// gl_TessLevelInner[0] = 4.0;
		// gl_TessLevelInner[1] = 4.0;

		// gl_TessLevelOuter[0] = 4.0; // -z
		// gl_TessLevelOuter[1] = 4.0; // -x
		// gl_TessLevelOuter[2] = 4.0; // z
		// gl_TessLevelOuter[3] = 4.0; // x

		gl_TessLevelOuter[0] = getTessFactO(0); // nz
		gl_TessLevelOuter[1] = getTessFactO(1); // nx
		gl_TessLevelOuter[2] = getTessFactO(2); // z
		gl_TessLevelOuter[3] = getTessFactO(3); // x
		gl_TessLevelInner[0] = gl_TessLevelInner[1] = getTessFactI(dis);
	}

	// gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
		e_position[gl_InvocationID] = c_position[gl_InvocationID];
	e_texcoord[gl_InvocationID] = c_texcoord[gl_InvocationID];
}
