/**********************************************************************
 * GLSL shader program to draw a singularly-coloured particle.
 * The colour is defined in the main program, as opposed to in this shader program.
 *
 * @author 	: Andrew Lang
 * @id 		: a1648205
 * @created 	: 2015-06-01
 * @project 	: CG Assignment 3
**********************************************************************/

#version 130
uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

uniform vec4 a_colour;
in vec3 a_vertex;

out vec4 colour;

void main(void) {
	colour = a_colour;
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(a_vertex, 1.0f);
}
