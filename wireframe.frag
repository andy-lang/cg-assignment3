#version 130

const int numberOfLights = 1; // number of light sources. CHANGE THIS IF YOU ADD MORE LIGHTS.
const float shininess = 32;

uniform vec3 lightPositions[numberOfLights]; // positions of each light source
uniform vec3 lightAmbients[numberOfLights]; // ambient values for each light source
uniform vec3 lightDiffuses[numberOfLights]; // diffuse values for each light source
uniform vec3 lightSpeculars[numberOfLights]; // specular values for each light source

uniform vec3 mtl_ambient; // ambient material value
uniform vec3 mtl_diffuse; // diffuse material value
uniform vec3 mtl_specular; // specular material value

uniform sampler2D tex_map;

in vec4 vertex;
//in vec4 colour;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColour;


vec3 phongLight(in vec4 position, in vec3 norm, in vec4 light_pos, in vec3 light_ambient, in vec3 light_diffuse, in vec3 light_specular) {
    vec3 s;
    if (light_pos.w == 0.0)
        // s is the direction from the light to the vertex
        s = normalize(light_pos.xyz);
    else
        s = normalize(vec3(light_pos - position));
        
    // v is the direction from the eye to the vertex
    vec3 v = normalize(-position.xyz);
    
    // r is the direction of light reflected from the vertex
    vec3 r = reflect( -s, norm );
    
    vec3 ambient = light_ambient * mtl_ambient;
	
    // The diffuse component
    float sDotN = max( dot(s,norm), 0.0 );
    
    vec3 diffuse = light_diffuse * mtl_diffuse * sDotN;
    
    // Specular component
    vec3 spec = vec3(0.0);
    if ( sDotN > 0.0 )
		spec = light_specular * mtl_specular * pow( max( dot(r,v), 0.0 ), shininess );
    
    return ambient + diffuse + spec;
}

void main(void) {
    //fragColour = colour * texture(tex_map, texCoord);
	fragColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	for (int i = 0; i < numberOfLights; i++) {
		fragColour.xyz = phongLight(vertex, normalize(normal), vec4(lightPositions[i],1.0), lightAmbients[i], lightDiffuses[i], lightSpeculars[i]);
	}

	fragColour = vec4(fragColour.xyz, 1.0f)*texture(tex_map, texCoord);
}
