#version 130

const int numberOfLights = 2; // number of light sources. CHANGE THIS IF YOU ADD MORE LIGHTS.

// constants for attenuation calculation
const float attnConst = 1.0;
const float attnLinear = 0.045;
const float attnQuad = 0.0075;

uniform vec3 lightPositions[numberOfLights]; // positions of each light source
uniform vec3 lightAmbients[numberOfLights]; // ambient values for each light source
uniform vec3 lightDiffuses[numberOfLights]; // diffuse values for each light source
uniform vec3 lightSpeculars[numberOfLights]; // specular values for each light source

uniform vec3 mtl_ambient; // ambient material value
uniform vec3 mtl_diffuse; // diffuse material value
uniform vec3 mtl_specular; // specular material value
uniform vec3 mtl_emission; // emission colour for the material
uniform float mtl_shininess; // shininess of the material

uniform sampler2D tex_map;

in mat4 lightPosMatrix;
in vec4 vertex;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColour;


// lovingly ripped from example code in lectures 5 & 7
vec3 phongLight(in vec4 position, in vec3 norm, in vec4 light_pos, in vec3 light_ambient, in vec3 light_diffuse, in vec3 light_specular) {
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

	float attenuation = 1 / (attnConst + attnLinear*dist + attnQuad*dist*dist); // attenuation factor, so that light fades with distance

    return ambient + attenuation * (diffuse + spec);
}

void main(void) {
	fragColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	for (int i = 0; i < numberOfLights; i++) {
		fragColour.xyz += phongLight(vertex, normalize(normal), lightPosMatrix*vec4(lightPositions[i], 1.0), lightAmbients[i], lightDiffuses[i], lightSpeculars[i]);
	}

	fragColour = clamp(vec4(fragColour.xyz + mtl_emission.xyz, 1.0f), 0.0, 1.0)*texture(tex_map, texCoord);
}
