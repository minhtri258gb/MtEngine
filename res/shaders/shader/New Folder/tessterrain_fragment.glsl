#version 430 core

in vec2 f_uvOvercoord;
in vec2 f_uvTilecoord;

out vec4 FragColor;

uniform sampler2D terrainTex;
uniform sampler2D heightMap;


void main(void)
{
	FragColor = texture(terrainTex, f_uvTilecoord);
//	FragColor = vec4(1.0);

//	float delta = 2000;
//	float offset = -1000;
//	float height = texture(heightMap, f_uvOvercoord).r;
//	height = (height - offset) / delta;
//	vec3 colorHeight = vec3(height);
//	FragColor = vec4(colorHeight, 1.0);
}
