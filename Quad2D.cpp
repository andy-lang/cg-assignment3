#include "Quad2D.hpp"

Quad2D::Quad2D(glm::vec3 position, glm::vec3 rotation, glm::vec4 colour, float scale, unsigned int programID)
{
	m_rotation = rotation;
	m_colour = colour;
	m_position = position;
	m_scale = scale;
	m_programID = programID;

	/*
	 * Create square vertex data
	 */
	// Top left point
	m_verticies.push_back(-1.0f);
	m_verticies.push_back(-1.0f);
	m_verticies.push_back(0.0f);

	// Top right point
	m_verticies.push_back(1.0f);
	m_verticies.push_back(-1.0f);
	m_verticies.push_back(0.0f);

	// Bottom left point
	m_verticies.push_back(-1.0f);
	m_verticies.push_back(1.0f);
	m_verticies.push_back(0.0f);

	// Bottom right point
	m_verticies.push_back(1.0f);
	m_verticies.push_back(1.0f);
	m_verticies.push_back(0.0f);

	/*
	 * Create index data
	 */
	// Top triangle
	m_indicies.push_back(0);
	m_indicies.push_back(1);
	m_indicies.push_back(2);

	// Bottom triangle
	m_indicies.push_back(1);
	m_indicies.push_back(2);
	m_indicies.push_back(3);

	calcModelMatrix();

	loadData();
}

void Quad2D::calcModelMatrix()
{
	m_modelMatrix = glm::mat4();
	// Move
	m_modelMatrix = glm::translate(m_modelMatrix, m_position);
	// Rotate
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	// Resize
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_scale, m_scale, m_scale));
	return;
}

void Quad2D::loadData()
{
	// Setup storage space on GPU
	glGenBuffers(BUFFER_COUNT, m_buffers);
	glGenVertexArrays(1, &m_vertexVAOHandle);

	// Load vertex data
	glBindVertexArray(m_vertexVAOHandle);
	int vertLoc = glGetAttribLocation(m_programID, "a_vertex");
	if (vertLoc == -1)
	{
		std::cout << "Can't find a_vertex" << std::endl;
		exit(1);
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[VERT_BUF_POS]);
	glBufferData(GL_ARRAY_BUFFER, m_verticies.size() * sizeof(float), &m_verticies.front(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertLoc);
	glVertexAttribPointer(vertLoc, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);

	// Load indices data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDI_BUF_POS]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(unsigned int), &m_indicies.front(), GL_STATIC_DRAW);

	// Unbind and we're done
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return;
}

void Quad2D::render()
{
	glDisable(GL_CULL_FACE);
	glUseProgram(m_programID);
	
	int colourHandle = glGetUniformLocation(m_programID, "a_colour");
	int modelHandle = glGetUniformLocation(m_programID, "model_matrix");
	if (modelHandle == -1 || colourHandle == -1)
	{
		std::cout << "Can't find a uniform" << std::endl;
		exit(1);
	}

	glBindVertexArray(m_vertexVAOHandle);
	glUniformMatrix4fv(modelHandle, 1, false, glm::value_ptr(m_modelMatrix));
	glUniform1fv(colourHandle, 1, glm::value_ptr(m_colour));
	glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glEnable(GL_CULL_FACE);
	return;
}
