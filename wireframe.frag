#version 130

const int numberOfLights = 1; // number of light sources
in vec4 lightPositions[numberOfLights]; // positions of each light source
in vec4 lightAmbients[numberOfLights]; // ambient values for each light source
in vec4 lightDiffuses[numberOfLights]; // diffuse values for each light source
in vec4 lightSpeculars[numberOfLights]; // specular values for each light source

uniform vec3 mtl_ambient; // ambient material value
uniform vec3 mtl_diffuse; // diffuse material value
uniform vec3 mtl_specular; // specular material value

uniform sampler2D tex_map;

in vec4 vertex;
in vec4 colour;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColour;

void main(void) {
    fragColour = colour * texture(tex_map, texCoord);
}
