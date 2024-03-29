#version 440 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texcoord;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in ivec4 v_boneIds;
layout (location = 4) in vec4 v_boneWeights;

out vec3 f_position;
out vec2 f_texcoord;
out vec3 f_normal;
out vec4 f_bw;

uniform mat4 bones[50];
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    f_bw = vec4(0);
    if(v_boneIds.x == 1)
        f_bw.z = v_boneIds.x;
    
    mat4 boneTransform  =  mat4(0.0);
    boneTransform += bones[v_boneIds.x] * v_boneWeights.x;
    boneTransform += bones[v_boneIds.y] * v_boneWeights.y;
    boneTransform += bones[v_boneIds.z] * v_boneWeights.z;
    boneTransform += bones[v_boneIds.w] * v_boneWeights.w;

    vec4 pos = boneTransform * vec4(v_position, 1.0);
    gl_Position = proj * view * model * pos;

    f_position = vec3(model * boneTransform * pos);
    f_texcoord = v_texcoord;
    f_normal = mat3(transpose(inverse(model * boneTransform))) * v_normal;
    f_normal = normalize(f_normal);
}
