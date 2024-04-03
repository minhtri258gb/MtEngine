#version 440 core

in vec2 f_texcoord;
in vec3 f_normal;
in vec3 f_trans_position; // model * position

out vec4 fragColor;

uniform sampler2D ourTexture;
uniform vec3 camPos;
uniform vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); // #TODO
uniform vec3 lightPos = vec3(-200.0f, 500.0f, -400.0f); // #TODO

void main()
{
	// Ambient light
	float ambient = 0.50f;

	// Cal diffuse light
	vec3 normal = normalize(f_normal);
	vec3 lightDirrection = normalize(lightPos - f_trans_position);
	float diffuse = max(dot(f_normal, lightDirrection), 0.0f);

	// Cal specular light
	float specularFactor = 3.0f; // 0.5
	vec3 viewDirection = normalize(camPos - f_trans_position);
	vec3 refectionDirection = reflect(-lightDirrection, f_normal);
	float specAmount = pow(max(dot(viewDirection, refectionDirection), 0.0f), 8);
	float specular = specAmount * specularFactor;

	// Main
	// if (f_normal.x > 0 && )
	fragColor = texture(ourTexture, f_texcoord) * lightColor * (diffuse + ambient + specular);
	// fragColor = texture(ourTexture, f_texcoord);
}
