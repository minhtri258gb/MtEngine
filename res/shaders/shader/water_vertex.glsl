#version 330 core

layout (location = 0) in vec2 v_position;

out vec2 f_uvcoord;
out vec3 f_fragPos;
out vec4 f_clipspace;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main(void)
{
    vec4 worldPos = model * vec4(v_position.x, 1.0, v_position.y, 1.0);

    f_clipspace = projection * view * worldPos;

    gl_Position = f_clipspace;

    f_uvcoord = worldPos.xz / 512.0;
    f_fragPos = worldPos.xyz;
}
