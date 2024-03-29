#version 440 core

in vec2 f_texcoord;
// in vec3 f_normal;
// in vec3 f_trans_position; // model * position

out vec4 fragColor;

uniform sampler2D ourTexture;
// uniform vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); // #TODO
// uniform vec3 lightPos = vec3(-200.0f, 500.0f, -400.0f); // #TODO


void main(void)
{
	// Ambient light
	// float ambient = 0.20f;

	// Cal diffuse light
	// vec3 normal = normalize(f_normal);
	// vec3 lightDirrection = normalize(lightPos - f_trans_position);
	// float diffuse = max(dot(f_normal, lightDirrection), 0.0f);

    // Main
	// fragColor = vec4(1, 1, 1, 1.0) * lightColor * (diffuse + ambient);
	// fragColor = texture(ourTexture, f_texcoord) * lightColor * (diffuse + ambient + specular);
    // fragColor = vec4(f_normal, 1.0);
	fragColor = texture(ourTexture, f_texcoord);
}
