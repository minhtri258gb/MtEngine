#version 440 core

in vec2 f_texcoord;

out vec4 fragColor;

uniform sampler2D texColor;


void main() {
	fragColor = texture(texColor, f_texcoord);
	// fragColor = vec4(0.0, 0.0, 0.0, 1.0); // #DEBUG
}
