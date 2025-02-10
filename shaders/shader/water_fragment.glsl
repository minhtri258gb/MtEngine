#version 330 core

in vec2 f_uvcoord;
in vec3 f_fragPos;
in vec4 f_clipspace;

out vec4 FragColor;

uniform sampler2D reflectTexture;
uniform sampler2D refractTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;
uniform vec3 sunDir;
uniform vec3 eyePos;
uniform float ambientFactor;
uniform float wavetime;

const float shineDamper = 20.0;
const float waveFactor = 0.02;


float lightFactor(vec2 texCoords, vec3 toEye, float depthFactor)
{
	// Diffuse
	float diff = max(dot(vec3(0,1,0), sunDir), 0.0);

	// Specular
	vec4 normalColor = texture(normalMap, texCoords);
	vec3 normal = vec3(normalColor.r * 2.0 - 1.0, normalColor.b, normalColor.g * 2.0 - 1.0);
	normal = normalize(normal);

	vec3 reflectedLight = reflect(-sunDir, normal);
	float specular = max(dot(reflectedLight, toEye), 0.0);
	specular = pow(specular, shineDamper);

	return ambientFactor * 0.5 + diff * 0.5 + specular * 1.6 * depthFactor;
}

vec4 waterTexture(vec3 toEye, vec2 spacecoord)
{
	float fresnelFactor = dot(toEye, vec3(0,1,0));
	fresnelFactor = pow(fresnelFactor, 0.5);
	vec4 reflectColor = texture(reflectTexture, spacecoord);
	vec4 refractColor = texture(refractTexture, spacecoord); // invert y
	return mix(reflectColor, refractColor, fresnelFactor);
}

float softEdges(vec2 spacecoord)
{
	float near = 1.0;
	float far = 20000.0;
	float depth = texture(depthMap, spacecoord).r;
	float floorDis = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	depth = gl_FragCoord.z;
	float waterDis = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	float waterDepth = floorDis - waterDis;
	//return clamp(waterDepth / 0.5, 0.0, 1.0);
	return clamp(waterDepth, 0.0, 1.0);
}

void main(void)
{
	vec3 toEye = normalize(eyePos - f_fragPos);
	vec2 spacecoord = (f_clipspace.xy / f_clipspace.w) / 2.0 + 0.5;
	float depthFactor = softEdges(spacecoord);

	vec2 distortedTexCoords = texture(dudvMap, vec2(f_uvcoord.x + wavetime, f_uvcoord.y)).rg * 0.1;
	distortedTexCoords = f_uvcoord + vec2(distortedTexCoords.x, distortedTexCoords.y + wavetime);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveFactor * depthFactor;
	spacecoord = clamp(spacecoord + totalDistortion, 0.001, 0.999); // chuyen dong va fix loi canh man hinh

	vec4 textureColor = waterTexture(toEye, spacecoord);

	vec3 totalColor = lightFactor(distortedTexCoords, toEye, depthFactor) * textureColor.xyz;
	totalColor = mix(totalColor, vec3(0.0, 0.3, 0.5), 0.2); // Lam nuoc xanh hon
	FragColor = vec4(totalColor, depthFactor);
}
