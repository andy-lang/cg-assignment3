/**********************************************************************
 * GLSL shader program for procedurally generating a granite-like texture, for the statue.
 *
 * @author 	: Andrew Lang, Riley Chase
 * @id 		: a1648205, a1647198
 * @created 	: 2015-06-05
 * @project 	: CG Assignment 3
**********************************************************************/

#version 130

const int numberOfLights = 8; // number of light sources. CHANGE THIS IF YOU ADD MORE LIGHTS.

// constants for attenuation calculation
const float attnConst = 0.98;
const float attnLinear = 0.025;
const float attnQuad = 0.01;

uniform vec3 lightPositions[numberOfLights]; // positions of each light source
uniform vec3 lightAmbients[numberOfLights]; // ambient values for each light source
uniform vec3 lightDiffuses[numberOfLights]; // diffuse values for each light source
uniform vec3 lightSpeculars[numberOfLights]; // specular values for each light source
uniform float lightBrightnesses[numberOfLights]; // brightnesses of each light.

uniform vec3 mtl_ambient; // ambient material value
uniform vec3 mtl_diffuse; // diffuse material value
uniform vec3 mtl_specular; // specular material value
uniform vec3 mtl_emission; // emission colour for the material
uniform float mtl_shininess; // shininess of the material

uniform sampler2D tex_map;
uniform sampler2D tex_norm;

in mat4 lightPosMatrix;
in vec4 vertex;
in vec4 vert;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColour;

// lovingly ripped from example code in lectures 5 & 7
vec3 phongLight(in vec4 position, in vec3 norm, in vec4 light_pos, in vec3 light_ambient, in vec3 light_diffuse, in vec3 light_specular, float light_brightness) {
    vec3 s;

    if (light_pos.w == 0.0) {
        // s is the direction from the light to the vertex
        s = normalize(light_pos.xyz);
	}
    else {
        s = normalize(vec3(light_pos - position));
	}
        
    // v is the direction from the eye to the vertex
    vec3 v = normalize(-position.xyz);
    
    // r is the direction of light reflected from the vertex
    vec3 r = reflect(-s, norm);
    
    vec3 ambient = clamp(light_ambient * mtl_ambient, 0.0, 1.0);
	
    // The diffuse component
    float sDotN = max( dot(s,norm), 0.0);
    
    vec3 diffuse = clamp(light_diffuse * mtl_diffuse * sDotN, 0.0, 1.0);
    
    // Specular component
    vec3 spec = vec3(0.0);
    if ( sDotN > 0.0 ) {
		spec = clamp(light_specular * mtl_specular * pow(max(dot(r,v), 0.0), mtl_shininess), 0.0, 1.0);
	}
    
	float dist = distance(position, light_pos); // distance between fragment and light

	float attenuation = light_brightness / (attnConst + attnLinear*dist + attnQuad*dist*dist); // attenuation factor, so that light fades with distance

    return ambient + attenuation * (diffuse + spec);
}

// The following functions were appropriated and modified from the proceduralTexture shader code found in lecture 10, originally written by Michael Hemsley and Anthony Dick.

float rand(vec2 co){ 
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
} 

void main(void) {
	fragColour = vec4(0.2f, 0.2f, 0.2f, 1.0f);
	
	// Normal Map
	vec3 NN = texture(tex_norm, texCoord.st).xyz;
	vec3 N = normal + normalize(2.0*NN.xyz-1.0);

	for (int i = 0; i < numberOfLights; i++) {
		fragColour.xyz += phongLight(vertex, normalize(N), lightPosMatrix*vec4(lightPositions[i], 1.0), lightAmbients[i], lightDiffuses[i], lightSpeculars[i], lightBrightnesses[i]);
	}

	vec4 colour;
	float fx = (1.0 + sin((vert.x + rand(10.0 * vert.xy)/2.0)*30.0))/2.0;
	if (fx < 0.6) {
		colour = vec4(0.9, 0.9, 0.9, 1.0);
	}
	else {
		colour = vec4(0.0, 0.0, 1.0, 1.0);
	}
	
	fragColour = vec4(fragColour.xyz + mtl_emission.xyz, 1.0f) * colour * texture2D(tex_map, texCoord);
}
