#version 330 core

in vec2 f_uvcoord;
in vec3 f_normal;
in mat3 f_TBN;
in vec4 f_shadowCoord;
in vec3 f_viewPos;
in vec3 f_fragPos;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D specularMap;
uniform sampler2D normalMap;
uniform sampler2D parallaxMap;
uniform sampler2D shadowMap;
uniform bool hasSpecularMap;
uniform bool hasNormalMap;
uniform bool hasParallaxMap;
uniform vec3 sunDir;
uniform float ambientFactor;

const float diffFactor = 0.5;
const float heightFactor = 0.1;


float lightFactor(vec2 texCoords)
{
	vec3 shadowCoord = f_shadowCoord.xyz / f_shadowCoord.w;
	shadowCoord = shadowCoord * 0.5 + 0.5;

	float shadowFactor = 0.0;

	if (shadowCoord.z < 1.0)
	{
		vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
		for (int x=-2; x<=2; x+=2)
		{
			for (int y=-2; y<=2; y+=2)
			{
				float pcfDepth = texture(shadowMap, shadowCoord.xy + vec2(x, y) * texelSize).r;
				shadowFactor += shadowCoord.z > pcfDepth ? 1.0 : 0.0;
			}
		}
		shadowFactor /= 9.0;
	}

    vec3 normalUnit = f_normal;
    if (hasNormalMap)
        normalUnit = normalize(2.0 * texture(normalMap, texCoords).rgb - 1.0);

    float diff = max(dot(normalUnit, sunDir), 0.0) * diffFactor;
    return ambientFactor + diff * (1.0 - shadowFactor);
}

vec2 parallaxMapping(vec2 texCoords, vec3 viewDir)
{
    const float minLayers = 8.0;
    const float maxLayers = 32.0;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    vec2 P = viewDir.xy * heightFactor;
    vec2 deltaTexCoords = P / numLayers;
    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = texture(parallaxMap, currentTexCoords).r;
    while (currentLayerDepth < currentDepthMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(parallaxMap, currentTexCoords).r;
        currentLayerDepth += layerDepth;
    }
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(parallaxMap, prevTexCoords).r - currentLayerDepth + layerDepth;
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);
    return finalTexCoords;
}

void main(void)
{
    vec2 texCoords = f_uvcoord;
    if (hasParallaxMap)
    {
        vec3 viewDir = normalize(f_viewPos - f_fragPos);
        texCoords = parallaxMapping(texCoords, viewDir);
        if (texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
            discard;
    }

    vec4 textureColor = texture(ourTexture, texCoords);

    vec3 totalColor = lightFactor(texCoords) * textureColor.xyz;

    FragColor = vec4(totalColor, 1.0);


}