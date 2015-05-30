#version 130
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

in vec3 a_vertex;
in vec3 a_normal;
in vec2 a_tex_coord;

out vec4 vertex;
out vec4 colour;
out vec3 normal;
out vec2 texCoord;

void main(void) {
    colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    texCoord = vec2(a_tex_coord.x, 1.0f - a_tex_coord.y); // need to invert tex coords' y value, due to disparity between how OBJ files and OpenGL implement texture mapping
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(a_vertex, 1.0f);
	vertex = vec4(a_vertex, 1.0f);
}
