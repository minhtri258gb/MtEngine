#version 430 core

layout (quads, fractional_even_spacing) in;

in vec2 te_position[];
in vec2 te_uvOvercoord[];
in int te_levelCell[];

out vec2 f_uvOvercoord;
out vec2 f_uvTilecoord;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform sampler2D heightMap;
uniform sampler1D stitchingTex0;
uniform sampler1D stitchingTex1;
uniform sampler1D stitchingTex2;
uniform sampler1D stitchingTex3;


const float terrainSize = 1024.0;


vec2 interpolate2(in vec2 v0, in vec2 v1, in vec2 v2, in vec2 v3)
{
	vec2 a = mix(v0, v1, gl_TessCoord.x);
	vec2 b = mix(v3, v2, gl_TessCoord.x);
	return mix(a, b, gl_TessCoord.y);
}

vec3 interpolate3(in vec3 v0, in vec3 v1, in vec3 v2, in vec3 v3)
{
	vec3 a = mix(v0, v1, gl_TessCoord.x);
	vec3 b = mix(v3, v2, gl_TessCoord.x);
	return mix(a, b, gl_TessCoord.y);
}

vec4 interpolate4(in vec4 v0, in vec4 v1, in vec4 v2, in vec4 v3)
{
	vec4 a = mix(v0, v1, gl_TessCoord.x);
	vec4 b = mix(v3, v2, gl_TessCoord.x);
	return mix(a, b, gl_TessCoord.y);
}

void main()
{
	vec2 position = interpolate2(te_position[0], te_position[1], te_position[2], te_position[3]);
	f_uvOvercoord = interpolate2(te_uvOvercoord[0], te_uvOvercoord[1], te_uvOvercoord[2], te_uvOvercoord[3]);

	float height = texture(heightMap, f_uvOvercoord).r;

	// Va cac zone
	//if (f_uvOvercoord.y == 0.0) height = -2000;//texture(stitchingTex0, f_uvOvercoord.x).r;
	//if (f_uvOvercoord.x == 0.0) height = -2000;//texture(stitchingTex1, f_uvOvercoord.y).r;
	//if (f_uvOvercoord.y == 1.0) height = -2000;//texture(stitchingTex2, f_uvOvercoord.x).r;
	//if (f_uvOvercoord.x == 1.0) height = -2000;//texture(stitchingTex3, f_uvOvercoord.y).r;

    gl_Position = projMat * viewMat * vec4(position, height, 1.0);

	f_uvTilecoord = position / 512.0;
}
