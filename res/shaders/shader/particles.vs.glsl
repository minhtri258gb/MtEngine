#version 440 core

layout (location = 0) in vec3 v_position;

uniform mat4 proj;
uniform mat4 view;

void main()
{
    gl_Position = proj * view * vec4(v_position, 1.0);
}
