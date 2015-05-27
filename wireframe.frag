#version 130

in vec4 colour;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColour;

uniform sampler2D tex_map;

void main(void) {
    fragColour = colour * texture(tex_map, texCoord);
}
