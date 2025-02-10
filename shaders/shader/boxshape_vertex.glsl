#version 330 core

layout (location = 0 ) in vec3 v_position;
layout (location = 1 ) in vec2 v_uvcoord;
layout (location = 2 ) in vec3 v_normal;

out vec2 f_uvcoord;
out vec3 f_normal;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;


void main(void)
{
    vec4 worldPos = modelMat * vec4(v_position, 1.0);

	gl_Position = projMat * viewMat * worldPos;

    f_normal = (modelMat * vec4(v_normal,0.0)).xyz;
    f_uvcoord = v_uvcoord;
}