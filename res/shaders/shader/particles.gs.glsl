#version 440 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 f_texcoord;

uniform mat4 proj;
uniform mat4 view;
uniform vec3 cameraPos;

void main()
{
    mat4 gVP = proj * view;
    vec3 pos = gl_in[0].gl_Position.xyz;

    vec3 toCamera = normalize(cameraPos - pos);
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(toCamera, up);

    pos -= (right * 0.5);
    gl_Position = gVP * vec4(pos, 1.0);
    f_texcoord = vec2(0.0, 0.0);
    EmitVertex();

    pos.y += 1.0;
    gl_Position = gVP * vec4(pos, 1.0);
    f_texcoord = vec2(0.0, 1.0);
    EmitVertex();

    pos.y -= 1.0;
    pos += right;
    gl_Position = gVP * vec4(pos, 1.0);
    f_texcoord = vec2(1.0, 0.0);
    EmitVertex();

    pos.y += 1.0;
    gl_Position = gVP * vec4(pos, 1.0);
    f_texcoord = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
} 