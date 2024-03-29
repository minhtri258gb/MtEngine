#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 0) in vec2 v_uvcoords;

out vec2 f_uvcoords;

uniform mat4 projview;
uniform mat4 model;

void main(void)
{
    gl_Position = projview * model * vec4(v_position, 1.0);
    f_uvcoords = v_uvcoords;
}