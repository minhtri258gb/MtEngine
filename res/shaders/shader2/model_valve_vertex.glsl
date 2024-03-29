#version 430 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_uvcoord;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in int v_boneid;
layout (location = 4) in int v_mtlid;

out vec2 f_uvcoord;
out vec3 f_normal;
flat out int f_mtlid;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
uniform mat4 bonesMat[64];
uniform float clipplane;


void main(void)
{
    // mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
    // BoneTransform += gBones[BoneIDs[1]] * Weights[1];
    // BoneTransform += gBones[BoneIDs[2]] * Weights[2];
    // BoneTransform += gBones[BoneIDs[3]] * Weights[3];

    // vec4 worldPos = modelMat * vec4(v_position, 1.0);
	vec4 worldPos = modelMat * bonesMat[v_boneid] * vec4(v_position, 1.0f);

	// gl_ClipDistance[0] = dot(worldPos, vec4(0,clipplane,0,0));
	gl_Position = projMat * viewMat * worldPos;

    f_normal = (modelMat * vec4(v_normal,0.0)).xyz;
    f_uvcoord = v_uvcoord;
    f_mtlid = v_mtlid;
}
