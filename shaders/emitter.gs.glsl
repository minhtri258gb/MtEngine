#version 440 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in float g_scale[];
in float g_progress[];

out vec4 f_texcoord;
out float f_blend;

uniform mat4 proj;
uniform mat4 view;
uniform vec3 cameraPos;
uniform ivec2 colrowNum; // x: col, y: row #TODO

const vec3 lockAxis = vec3(0,0,0);


vec4 calVertice()
{
    return vec4(0,0,0,0);
}

vec4 calTexcoord(vec2 texcoord, vec2 sizeCoord, vec2 offsetCoord1, vec2 offsetCoord2)
{
    vec2 onesizeCoord = texcoord * sizeCoord;
    return vec4(onesizeCoord + offsetCoord1, onesizeCoord + offsetCoord2);
}

void main()
{
    // Caculate texcoord
    vec2 sizeCoord = vec2(1.0f / colrowNum.x, 1.0f / colrowNum.y);
    float atlasProgress = g_progress[0] * (colrowNum.x * colrowNum.y - 1);
    int index = int(floor(atlasProgress));
    float blend = atlasProgress - index;
    vec2 offsetCoord1 = vec2(1.0f * (index % colrowNum.x) / colrowNum.x, 1.0f * (index / colrowNum.x) / colrowNum.y);
    index++;
    vec2 offsetCoord2 = vec2(1.0f * (index % colrowNum.x) / colrowNum.x, 1.0f * (index / colrowNum.x) / colrowNum.y);

    // Cal first
    mat4 gVP = proj * view;
    vec3 pos = gl_in[0].gl_Position.xyz;

    vec3 toCamera = normalize(cameraPos - pos);
    vec3 right, up;

    if (length(lockAxis) > 0) // Truong hop khoa doc hoac khac
    {
        right = normalize(-cross(toCamera, lockAxis)) / 2;
        up = normalize(lockAxis) / 2;
    }
    else // Truong hop ko khoa huong
    {
        right = normalize(-cross(toCamera, vec3(0,1,0))) / 2;
        up = normalize(cross(toCamera, right)) / 2;
    }

    // Pass for all vertives
    f_blend = blend;

    // Emit vertives
    gl_Position = gVP * vec4(pos + up - right, 1.0);
    f_texcoord = calTexcoord(vec2(0.0, 0.0), sizeCoord, offsetCoord1, offsetCoord2);
    EmitVertex(); // top, left

    gl_Position = gVP * vec4(pos - up - right, 1.0);
    f_texcoord = calTexcoord(vec2(0.0, 1.0), sizeCoord, offsetCoord1, offsetCoord2);
    EmitVertex(); // down, left

    gl_Position = gVP * vec4(pos + up + right, 1.0);
    f_texcoord = calTexcoord(vec2(1.0, 0.0), sizeCoord, offsetCoord1, offsetCoord2);
    EmitVertex(); // top, right

    gl_Position = gVP * vec4(pos - up + right, 1.0);
    f_texcoord = calTexcoord(vec2(1.0, 1.0), sizeCoord, offsetCoord1, offsetCoord2);
    EmitVertex(); // down, right

    EndPrimitive();
}
