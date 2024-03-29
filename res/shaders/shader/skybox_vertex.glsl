#version 330 core

layout (location = 0 ) in vec3 v_position;

out vec3 f_uvoord;

uniform mat4 projection;
uniform mat4 view;
uniform bool isReflect;


void main(void)
{
	vec4 worldPos = vec4(v_position, 1.0);

	gl_ClipDistance[0] = dot(worldPos, vec4(0,1,0,0));
	gl_Position = projection * view * worldPos;

	f_uvoord = v_position;// * mat3(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0); // #ZtoY

	if (isReflect)
	    f_uvoord.x = -f_uvoord.x;
}