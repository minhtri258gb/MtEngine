#version 330 core

in vec2 position;

out vec2 uvcoord;

uniform mat4 projection;
uniform mat4 model;


void main(void)
{
    gl_Position = projection * model * vec4(position, 0.0, 1.0);

    uvcoord = vec2(0.0);
    if (position.x > 0.0) uvcoord.x = 1.0;
    if (position.y > 0.0) uvcoord.y = 1.0;
}
