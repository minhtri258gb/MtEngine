#version 330 core

in vec3 position;
in vec3 normal;
in vec2 textureCoord;
in ivec3 bone;
in vec3 weight;

out vec2 pass_textureCoord;
out vec3 pass_normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void)
{
    pass_textureCoord = textureCoord;
    pass_normal = normal;

    gl_Position = projection * view * model * vec4(position, 1.0);
}
