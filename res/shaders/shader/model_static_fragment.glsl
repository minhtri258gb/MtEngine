#version 330 core

in vec2 f_uvcoord;
in vec3 f_normal;

out vec4 FragColor;

uniform sampler2D modelTexture;
uniform sampler2D specularMap;
uniform sampler2D normalMap;
uniform sampler2D parallaxMap;
uniform sampler2D shadowMap;
uniform bool hasSpecularMap;
uniform bool hasNormalMap;
uniform bool hasParallaxMap;
uniform vec3 sunDir;
uniform float ambientFactor;

const float diffFactor = 0.01;
const float heightFactor = 0.1;


float lightFactor(vec2 texCoords)
{
	// vec3 shadowCoord = f_shadowCoord.xyz / f_shadowCoord.w;
	// shadowCoord = shadowCoord * 0.5 + 0.5;

	// float shadowFactor = 0.0;

	// if (shadowCoord.z < 1.0)
	// {
	// 	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	// 	for (int x=-2; x<=2; x+=2)
	// 	{
	// 		for (int y=-2; y<=2; y+=2)
	// 		{
	// 			float pcfDepth = texture(shadowMap, shadowCoord.xy + vec2(x, y) * texelSize).r;
	// 			shadowFactor += shadowCoord.z > pcfDepth ? 1.0 : 0.0;
	// 		}
	// 	}
	// 	shadowFactor /= 9.0;
	// }

    vec3 normalUnit = f_normal;
    // if (hasNormalMap)
    //     normalUnit = normalize(2.0 * texture(normalMap, texCoords).rgb - 1.0);

    float diff = max(dot(normalUnit, sunDir), 0.0) * diffFactor;
    return ambientFactor + diff;
    // return ambientFactor + diff * (1.0 - shadowFactor);
}

void main(void)
{
    vec2 texCoords = f_uvcoord;
    // parallax
    vec4 textureColor = texture(modelTexture, texCoords);
    vec3 totalColor = lightFactor(texCoords) * textureColor.xyz;
    FragColor = vec4(totalColor, 1.0);
}