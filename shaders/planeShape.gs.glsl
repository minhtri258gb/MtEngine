#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 g_uvcoord[];

out vec2 f_uvcoord;

void main(void)
{
    gl_Position = gl_in[0].gl_Position;
    f_uvcoord = g_uvcoord[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    f_uvcoord = g_uvcoord[1];
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    f_uvcoord = g_uvcoord[2];
    EmitVertex();

    EndPrimitive();
}
