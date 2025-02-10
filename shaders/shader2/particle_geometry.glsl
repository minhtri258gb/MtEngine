#version 430 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in float g_scale[];
in float g_process[];

out vec4 f_uvcoord;
out float f_blend;

uniform float screenRatio;
uniform int nRow;
uniform int nFrame;


void uvAtlas(int id)
{
	float atlasProcess = g_process[0] * (nFrame - 1);

	int index = int(floor(atlasProcess));
	float cellRow = 1.0 / nRow;
	float cellCol = cellRow;
	if (nRow * nRow != nFrame)
		cellCol = ceil(nFrame / nRow);

	f_uvcoord.x = (index % nRow) * cellRow;
	f_uvcoord.y = (index / nRow) * cellCol;
	index++;
	f_uvcoord.z = (index % nRow) * cellRow;
	f_uvcoord.w = (index / nRow) * cellCol;

	if (id == 2 || id == 3)
		f_uvcoord.xz += vec2(cellRow, cellCol);
	if (id == 0 || id == 2)
		f_uvcoord.yw += vec2(cellRow, cellCol);

	f_blend = mod(atlasProcess, 1.0f);
}

void main(void)
{
	float size1 = g_scale[0];
	float size2 = size1 * screenRatio;

	gl_Position = gl_in[0].gl_Position + vec4(-size1,  size2, 0.0, 0.0);
	uvAtlas(0); // f_uvcoord = vec4(0,1,0,1);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(-size1, -size2, 0.0, 0.0);
	uvAtlas(1); // f_uvcoord = vec4(0,0,0,0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4( size1,  size2, 0.0, 0.0);
	uvAtlas(2); // f_uvcoord = vec4(1,1,1,1);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4( size1, -size2, 0.0, 0.0);
	uvAtlas(3); // f_uvcoord = vec4(1,0,1,0);
	EmitVertex();

	EndPrimitive();
}
