#version 330 core

in vec2 f_uvcoord;
// in vec4 f_shadowCoord;

out vec4 out_Color;

uniform sampler2D ourTexture;
// uniform sampler2D shadowMap;
// uniform float ambientFactor;
// uniform vec3 sunDir;

// const float diffFactor = 1.0;


// float lightFactor()
// {
// 	vec3 shadowCoord = f_shadowCoord.xyz / f_shadowCoord.w;
// 	shadowCoord = shadowCoord * 0.5 + 0.5;

// 	float shadowFactor = 0.0;

// 	if (shadowCoord.z < 1.0)
// 	{
// 		vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
// 		for (int x=-2; x<=2; x+=2)
// 		{
// 			for (int y=-2; y<=2; y+=2)
// 			{
// 				float pcfDepth = texture(shadowMap, shadowCoord.xy + vec2(x, y) * texelSize).r;
// 				shadowFactor += shadowCoord.z > pcfDepth ? 1.0 : 0.0;
// 			}
// 		}
// 		shadowFactor /= 9.0;
// 	}

// 	float diff = max(dot(vec3(0,1,0), sunDir), 0.0) * diffFactor;
// 	return ambientFactor + diff * (1.0 - shadowFactor);
// }

void main(void)
{
	// vec4 textureColor = texture(groundTexture, f_uvcoord);
	// vec3 totalColor = lightFactor() * textureColor.xyz;
	// out_Color = vec4(totalColor, 1.0);

	vec4 textureColor = texture(ourTexture, f_uvcoord);
	out_Color = vec4(textureColor.xyz,1);
}
