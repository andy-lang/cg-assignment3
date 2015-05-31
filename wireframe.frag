#version 130

in vec4 colour;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColour;

uniform sampler2D tex_map;
uniform sampler2D tex_norm;

void main(void) {
	// Normal Map
	vec3 NN = texture(tex_norm, texCoord.st).xyz;
	vec3 N = normal + normalize(2.0*NN.xyz-1.0);

	//fragColour = colour * texture(tex_map, texCoord);
	fragColour = vec4(fragColour.xyz, 1.0) * texture(tex_map, texCoord.st);
}
