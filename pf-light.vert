#version 130
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat3 normal_matrix;

in vec3 a_vertex;
in vec3 a_normal;
in vec2 a_tex_coord;

out vec4 vertex;
out vec3 normal;
out vec2 texCoord;

void main(void) {
    texCoord = vec2(a_tex_coord.x, 1.0f - a_tex_coord.y); // need to invert tex coords' y value, due to disparity between how OBJ files and OpenGL implement texture mapping

	normal = normalize(normal_matrix * a_normal);
	vertex = view_matrix * model_matrix * vec4(a_vertex, 1.0f);
    gl_Position = projection_matrix * vertex;
}
