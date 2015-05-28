/**********************************************************************
 * Functionality to compile a GLSL shader, and print any errors that occur.
 * Lovingly ripped from previous lecture examples.
 *
 * @author 	: Andrew Lang
 * @id 		: a1648205
 * @created 	: 2015-05-07
 * @project 	: CG Assignment 3
**********************************************************************/

#ifndef SHADER_HPP
#define SHADER_HPP

GLuint LoadShaders(const char* vertex_file_path, const char *fragment_file_path);

#endif
