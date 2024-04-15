#version 440 core

layout(quads, equal_spacing, ccw) in;
// layout (quads) in;

in vec2 e_position[];
in vec2 e_texcoord[];

out vec2 f_texcoord;

uniform mat4 proj;
uniform mat4 view;
uniform sampler2D texHeight; // at TerrainPath
uniform float heightScale; // at TerrainPath


// vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
// {
//     return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
// }

// vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
// {
//     return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
// }

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2, vec2 v3)
{
	vec2 p1 = mix(v0, v1, gl_TessCoord.x);
	vec2 p2 = mix(v2, v3, gl_TessCoord.x);
	return mix(p1, p2, gl_TessCoord.y);
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2, vec3 v3)
{
	vec3 p1 = mix(v0, v1, gl_TessCoord.x);
	vec3 p2 = mix(v2, v3, gl_TessCoord.x);
	return mix(p1, p2, gl_TessCoord.y);
}

vec4 interpolate4D(vec4 v0, vec4 v1, vec4 v2, vec4 v3)
{
	vec4 p1 = mix(v0, v1, gl_TessCoord.x);
	vec4 p2 = mix(v2, v3, gl_TessCoord.x);
	return mix(p1, p2, gl_TessCoord.y);
}

void main()
{
	// Textcoord
	f_texcoord = interpolate2D(e_texcoord[0], e_texcoord[1], e_texcoord[2], e_texcoord[3]);

	// float height = 0.0;

	// Position
	// vec4 p1 = mix(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_TessCoord.x);
	// vec4 p2 = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, gl_TessCoord.x);
	// vec4 pos = mix(p1, p2, gl_TessCoord.y);
	// vec4 pos = interpolate4D(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position, gl_in[3].gl_Position);
	// pos.y = height;

	// Position
	vec2 pos = interpolate2D(e_position[0], e_position[1], e_position[2], e_position[3]);

	float height = texture(texHeight, f_texcoord).r * heightScale;
	// float height = 0.0;

	gl_Position = proj * view * vec4(pos.x, height, pos.y, 1.0);
}
