#version 130
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

in vec3 a_vertex;
in vec3 a_normal;

out vec4 colour;

void main(void) {
    colour = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(a_vertex, 1.0f);
}
