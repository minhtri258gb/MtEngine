#version 430 core

in vec2 v_position;

out vec2 f_uvcoord;

uniform mat4 projMat;


void main(void)
{
    gl_Position = projMat * vec4(v_position, 0.0, 1.0);

    f_uvcoord = vec2(0.0);
    if (v_position.x > 0.0)
        f_uvcoord.x = 1.0;
    if (v_position.y > 0.0)
        f_uvcoord.y = 1.0;
}
