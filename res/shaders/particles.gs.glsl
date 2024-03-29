#version 440 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 f_texcoord;

uniform mat4 proj;
uniform mat4 view;
uniform vec3 cameraPos;

const vec3 lockAxis = vec3(0,0,0);

void main()
{
    mat4 gVP = proj * view;
    vec3 pos = gl_in[0].gl_Position.xyz;

    vec3 toCamera = normalize(cameraPos - pos);
    vec3 right, up;

    if (length(lockAxis) > 0)
    {
        right = normalize(-cross(toCamera, lockAxis)) / 2; // ?
        up = normalize(lockAxis) / 2;
    }
    else
    {
        right = normalize(cross(toCamera, vec3(0,1,0))) / 2;
        up = normalize(cross(toCamera, right)) / 2;
    }

    gl_Position = gVP * vec4(pos + up - right, 1.0);
    f_texcoord = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = gVP * vec4(pos - up - right, 1.0);
    f_texcoord = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = gVP * vec4(pos + up + right, 1.0);
    f_texcoord = vec2(1.0, 1.0);
    EmitVertex();

    gl_Position = gVP * vec4(pos - up + right, 1.0);
    f_texcoord = vec2(1.0, 0.0);
    EmitVertex();

    EndPrimitive();
}
