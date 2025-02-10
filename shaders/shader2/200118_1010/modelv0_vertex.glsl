#version 330 core

layout (location = 0 ) in vec3 v_position;
layout (location = 1 ) in vec2 v_uvcoord;
layout (location = 2 ) in vec3 v_normal;
layout (location = 3 ) in vec3 v_tangent;
layout (location = 4 ) in vec3 v_bitangent;

out vec2 f_uvcoord;
out vec3 f_normal;
out mat3 f_TBN;
out vec4 f_shadowCoord;
out vec3 f_viewPos;
out vec3 f_fragPos;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
uniform mat4 shadowSpace;
uniform vec3 eyePos;
uniform float clipplane;

void main(void)
{
    vec4 worldPos = modelMat * vec4(v_position, 1.0);

	gl_ClipDistance[0] = dot(worldPos, vec4(0,clipplane,0,0));
	gl_Position = projMat * viewMat * worldPos;

    f_normal = (modelMat * vec4(v_normal,0.0)).xyz;
    f_uvcoord = v_uvcoord;

    vec3 T = normalize(mat3(modelMat) * v_tangent);
    vec3 B = normalize(mat3(modelMat) * v_bitangent);
    vec3 N = normalize(mat3(modelMat) * v_normal);
    f_TBN = transpose(mat3(T, B, N));

    f_shadowCoord = shadowSpace * worldPos;

    f_viewPos = f_TBN * eyePos;
    f_fragPos = f_TBN * worldPos.xyz;
}