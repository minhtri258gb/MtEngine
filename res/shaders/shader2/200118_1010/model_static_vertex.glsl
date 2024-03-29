#version 330 core

in vec3 position;
in vec3 normal;
in vec2 textureCoords;

out vec2 pass_textureCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void)
{
    pass_textureCoords = textureCoords;

    gl_Position = projection * view * model * vec4(position, 1.0);
}