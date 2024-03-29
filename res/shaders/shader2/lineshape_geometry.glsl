#version 430 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 f_uvcoord;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform vec3 startPos;
uniform vec3 endPos;
uniform vec3 eyePos;
uniform float thinkness;
uniform float lengthPath;


void main(void)
{
    vec3 toRight = normalize(cross(endPos - startPos, eyePos - startPos)) * thinkness;
    float uvLength = distance(startPos, endPos) / lengthPath;

	gl_Position = projMat * viewMat * vec4(startPos - toRight, 1.0);
    f_uvcoord = vec2(0,0);
    EmitVertex();
    gl_Position = projMat * viewMat * vec4(startPos + toRight, 1.0);
    f_uvcoord = vec2(1,0);
    EmitVertex();
    gl_Position = projMat * viewMat * vec4(endPos - toRight, 1.0);
    f_uvcoord = vec2(0,uvLength);
    EmitVertex();
    gl_Position = projMat * viewMat * vec4(endPos + toRight, 1.0);
    f_uvcoord = vec2(1,uvLength);
    EmitVertex();
    EndPrimitive();
}
