#version 440 core

layout (location = 0 ) in vec3 v_position;
layout (location = 1 ) in vec2 v_texcoord;
layout (location = 2 ) in vec2 v_lmapcoord;

// out vec2 f_texcoord;
// out vec3 f_trans_position; // model * position

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;


void main(void)
{
    // Pass
    // f_texcoord = v_texcoord;
    // f_normal = vec3(model * vec4(v_normal, 1.0));
	// f_trans_position = vec3(model * vec4(v_position, 1.0f));

    // Main
	// gl_Position = proj * view * vec4(f_trans_position, 1.0f);
	gl_Position = proj * view * model * vec4(v_position, 1.0f);
}
