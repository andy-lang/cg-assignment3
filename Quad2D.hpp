/**********************************************************************
 * Simple 2D quadrilateral surface rendered with OpenGL. For now, and until required, it is a simple 1x1 square positioned in the world.
 *
 * @author	:	Riley Chase
 * @id		:	a1647198
 * @created	:	2015-06-07
 * @project	:	CG assignment 3
**********************************************************************/

#ifndef QUAD2d_H
#define QUAD2d_H

#include <GL/glew.h>
#include <GL/glut.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "./libs/Lib.h"

#include <vector>
#include <iostream>

class Quad2D
{
public:
	/*
	 * Construct and arbitrary sized quadrilateral surface within the world space.
	 *
	 * @param1 	pos1 : The point in 3D space that corresponds to one of two opposite corners of the square.
	 * @param2 	pos2 : The second point of the square. These two points must lie **exactly** on the same line in one of the 3 dimensions
	 */
	Quad2D(glm::vec3 position, glm::vec3 rotation, glm::vec4 colour, float scale, unsigned int programID);

	/*
	 * Renders the Quad to the scene
	 */
	void render();
private:
	// An 'empty' Quad is nonsensical, so hide the default constructor
	Quad2D();

	/*
	 * Recalculates the model matrix.
	 */
	void calcModelMatrix();

	/*
	 * Loads the vertex and index data to the GPU and sets that value of m_vertexVAOHandle
	 */
	void loadData();

	// OpenGL Related Named Constants
	static const unsigned int BUFFER_COUNT = 2;
	static const unsigned int VERT_BUF_POS = 0;
	static const unsigned int INDI_BUF_POS = 1;

	std::vector<float> m_verticies;
	std::vector<unsigned int> m_indicies;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec4 m_colour;
	float m_scale;
	unsigned int m_programID;
	glm::mat4 m_modelMatrix;
	unsigned int m_buffers[BUFFER_COUNT];
	unsigned int m_vertexVAOHandle;
};

#endif // QUAD2d_H
