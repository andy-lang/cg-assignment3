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
in vec4 colour;

out vec4 fragColour;

void main(void) {
	fragColour = colour;
}
