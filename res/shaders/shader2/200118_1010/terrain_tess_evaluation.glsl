#version 330 core

layout (location = 0 ) in vec3 v_position;
layout (location = 1 ) in vec2 v_uvoord;

out vec2 f_uvoord;

uniform mat4 projection;
uniform mat4 view;

void main(void)
{
    gl_ClipDistance[0] = 0;
    gl_Position = projection * view * vec4(v_position, 1.0);

    f_uvoord = v_uvoord;
}