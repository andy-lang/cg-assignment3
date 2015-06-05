/**********************************************************************
 * GLSL shader program to calculate per-fragment lights using the Phong shading model.
 * This is the 'default' shader program that most objects are rendered to.
 *
 * @author 	: Andrew Lang, Riley Chase
 * @id 		: a1648205, a1647198
 * @created 	: 2015-05-07
 * @project 	: CG Assignment 3
**********************************************************************/

#version 130
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat3 normal_matrix;

in vec3 a_vertex;
in vec3 a_normal;
in vec2 a_tex_coord;

out mat4 lightPosMatrix;
out vec4 vertex;
out vec4 vert;
out vec3 normal;
out vec2 texCoord;

void main(void) {
    texCoord = vec2(a_tex_coord.x, 1.0f - a_tex_coord.y); // need to invert tex coords' y value, due to disparity between how OBJ files and OpenGL implement texture mapping

	lightPosMatrix = view_matrix;
	normal = normalize(normal_matrix * a_normal);
	vertex = view_matrix * model_matrix * vec4(a_vertex, 1.0f);
	vert = vec4(a_vertex, 1.0f); // used by textural procedural calculations
    gl_Position = projection_matrix * vertex;

}
