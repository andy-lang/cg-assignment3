/**********************************************************************
 * GLSL shader program for procedurally generating a marble-like texture, for the statue.
 *
 * @author 	: Andrew Lang, Riley Chase
 * @id 		: a1648205, a1647198
 * @created 	: 2015-06-01
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
vec4 mod289(vec4 x) {
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x) {
    return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r) {
    return 1.79284291400159 - 0.85373472095314 * r;
}

vec2 fade(vec2 t) {
    return t*t*t*(t*(t*6.0-15.0)+10.0);
}

float pnoise(vec2 P, vec2 rep) {
    vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
    vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
    Pi = mod(Pi, rep.xyxy); // To create noise with explicit period
    Pi = mod289(Pi);        // To avoid truncation effects in permutation
    vec4 ix = Pi.xzxz;
    vec4 iy = Pi.yyww;
    vec4 fx = Pf.xzxz;
    vec4 fy = Pf.yyww;
    
    vec4 i = permute(permute(ix) + iy);
    
    vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
    vec4 gy = abs(gx) - 0.5 ;
    vec4 tx = floor(gx + 0.5);
    gx = gx - tx;
    
    vec2 g00 = vec2(gx.x,gy.x);
    vec2 g10 = vec2(gx.y,gy.y);
    vec2 g01 = vec2(gx.z,gy.z);
    vec2 g11 = vec2(gx.w,gy.w);
    
    vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
    g00 *= norm.x;
    g01 *= norm.y;
    g10 *= norm.z;
    g11 *= norm.w;
    
    float n00 = dot(g00, vec2(fx.x, fy.x));
    float n10 = dot(g10, vec2(fx.y, fy.y));
    float n01 = dot(g01, vec2(fx.z, fy.z));
    float n11 = dot(g11, vec2(fx.w, fy.w));
    
    vec2 fade_xy = fade(Pf.xy);
    vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
    float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
    return 2.3 * n_xy;
}

void main(void) {
	fragColour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Normal Map
	vec3 NN = texture(tex_norm, texCoord.st).xyz;
	vec3 N = normal + normalize(2.0*NN.xyz-1.0);

	for (int i = 0; i < numberOfLights; i++) {
		fragColour.xyz += phongLight(vertex, normalize(N), lightPosMatrix*vec4(lightPositions[i], 1.0), lightAmbients[i], lightDiffuses[i], lightSpeculars[i], lightBrightnesses[i]);
	}

	/*
	float f1 = pnoise(vert.xz, vert.xz);
	float f2 = pnoise(vert.xz, vert.yz);
	float f3 = pnoise(vert.yz, vert.zx);
	float f4 = pnoise(vert.zx, vert.xy);

	float f5 = (f1/f2) + (f3/f4);
	*/

	/* float shapeFunc = f5; */
	//float shapeFunc = (1+sin((vert.y + pnoise(5.0*vert.xy, 5.0*vert.yz)/2.0)*20.0))/2.0;
	float shapeFunc = (1.0 + sin(pnoise(vert.yy, vert.yy)/50.0f)*2.0f)/2.0;
	fragColour = vec4(fragColour.xyz + mtl_emission.xyz, 1.0f) * vec4(shapeFunc, shapeFunc, shapeFunc, 1.0f) * texture2D(tex_map, texCoord);
}
