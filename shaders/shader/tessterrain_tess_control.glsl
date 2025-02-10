#version 430 core

layout(vertices = 4) out;

in vec2 tc_position[];
in vec2 tc_uvOvercoord[];
in int tc_levelCell[];
in int tc_patchCell[];

out vec2 te_position[];
out vec2 te_uvOvercoord[];
out int te_levelCell[];

uniform mat4 projMat;
uniform mat4 viewMat;
uniform sampler2D heightMap;
uniform vec3 eyePos;


//uniform int maxTrianglesPerTexel = 10;
//uniform float horizontalScale = 10.0;
//uniform float verticalScale = 0.4;
//uniform mat4 mvp;
//const float pixelsPerTriangleEdge = 12.0;
//const vec2 viewportSize = {1280.0, 720.0};
//const float tessellationLevel = 64.0;
//const float maxTessLevel = 64.0;
//const float lod_factor = 2.0;
//const int maxTrianglesPerTexel = 10;


//void main()
//{
//	if (gl_InvocationID == 0)
//	{
//		mat4 mvp = projMat * viewMat;
//		vec4 clipSpace[4];
//		for (int i=0; i<4; i++)
//		{
//			vec4 position;
//			position.xz = tc_position[i];
//			position.y = texture(heightMap, position.xz).r;
//			position.w = 1.0;
//
//			clipSpace[i] = mvp * position;
//		}
//	}
//
//	te_position[gl_InvocationID] = tc_position[gl_InvocationID];
//}
//	0	1	2	3	4	5	6	7
//	1	2	4	8	16	32	64	128
//
//
//
//
float getTessFactO(int id)
{
	float fact = 4.0;
	if (id == 0 && (tc_patchCell[0] & (1 << 0)) != 0)
		fact = fact / 2;
	if (id == 1 && (tc_patchCell[1] & (1 << 1)) != 0)
		fact = fact / 2;
	if (id == 2 && (tc_patchCell[2] & (1 << 2)) != 0)
		fact = fact / 2;
	if (id == 3 && (tc_patchCell[3] & (1 << 3)) != 0)
		fact = fact / 2;

	return fact;
}

/*
dis = (dis - osD) / dtD
dis = 1 - dis ; flip
dis * dtL + osL
*/
float getTessFactI(float dis)
{
	if (tc_levelCell[0] == 1)
		return clamp((352 - dis) / 24, 4.0, 12.0);
	else if (tc_levelCell[0] <= 7)
		return clamp(12 - dis/(1 << (4 + tc_levelCell[0])), 4.0, 8.0);
	return 2.0;
}

void main()
{
//	mat4 mvp = projMat * viewMat;
//	vec4 clipSpace[4];
//	for (int i=0; i<4; i++)
//	{
//		vec4 position;
//		position.xz = tc_position[i];
//		position.y = texture(heightMap, position.xz).r;
//		position.w = 1.0;
//
//		clipSpace[i] = mvp * position;
//	}


//	float df = 1280.0 * 720 * 0.01;
//	float dist = df - distance(eyePos, vec3(tc_position[gl_InvocationID].x, tc_position[gl_InvocationID].y, height));
//	dist /= df;
//	dist = pow(dist, 5);
//
//	float tessfact = dist * 5;
//	tessfact = max(2, tessfact);

	float height = texture(heightMap, tc_uvOvercoord[0]).r;
	float dis = distance(eyePos, vec3(tc_position[gl_InvocationID].x, height, tc_position[gl_InvocationID].y));

	gl_TessLevelOuter[0] = getTessFactO(0); // l
	gl_TessLevelOuter[1] = getTessFactO(1); // b
	gl_TessLevelOuter[2] = getTessFactO(2); // r
	gl_TessLevelOuter[3] = getTessFactO(3); // f
	gl_TessLevelInner[0] = gl_TessLevelInner[1] = getTessFactI(dis);


//	if ((tc_patchCell[0] & (1 << 0)) != 0)
//		gl_TessLevelOuter[0] = 1.0;
//	else
//		gl_TessLevelOuter[0] = 2.0;
//	if ((tc_patchCell[1] & (1 << 1)) != 0)
//		gl_TessLevelOuter[1] = 1.0;
//	else
//		gl_TessLevelOuter[1] = 2.0;
//	if ((tc_patchCell[2] & (1 << 3)) != 0)
//		gl_TessLevelOuter[2] = 1.0;
//	else
//		gl_TessLevelOuter[2] = 2.0;
//	if ((tc_patchCell[3] & (1 << 2)) != 0)
//		gl_TessLevelOuter[3] = 1.0;
//	else
//		gl_TessLevelOuter[3] = 2.0;

	te_position[gl_InvocationID] = tc_position[gl_InvocationID];
	te_uvOvercoord[gl_InvocationID] = tc_uvOvercoord[gl_InvocationID];
	te_levelCell[gl_InvocationID] = tc_levelCell[gl_InvocationID];
}