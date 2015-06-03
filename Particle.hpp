/**********************************************************************
 * A single Particle object, and associated data.
 *
 * @author	:	Andrew Lang
 * @id		:	a1648205
 * @created :	2015-06-02
 * @project	:	CG assignment 3
**********************************************************************/

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "external_files/soil/src/SOIL.h"
#include "external_files/tiny_obj_loader/tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include <iostream>
#include <vector>
#include <cstdlib>

class Particle {
public:
	/* Sole Particle constructor.
	 * @param	position	The position at which the particle will be initialised.
	 * @param	colour		The colour of the particle.
	 * @param	speed	The speed at which the particle is travelling.
	 * @param	programTime	The current time of the program. Used for checking by the ParticleGenerator regarding how long the particle has been alive, and thus whether it should be deleted.
	 * @param	indicesOffset An offset of the indices, relative to the object's position in the buffer.
	 */
    Particle(glm::vec3 position, glm::vec4 colour, float speed, unsigned int programTime, unsigned int indicesOffset = 0);
    ~Particle();

	/* Returns the program time at which the particle was created. */
	unsigned int getBirthTime() const;
	void setBirthTime(unsigned int birthTime);

	std::vector<float> getVertexData() const;
	std::vector<unsigned int> getIndexData() const;

	unsigned int getVerticesSize() const;
	unsigned int getIndicesSize() const;

	glm::vec4 getColour();

	/* Updates the model matrix, relative to the Particle's properties (eg position, speed, etc), then return this model matrix. */
	glm::mat4 updateModelMatrix();

	/* Returns the model matrix without updating. */
	glm::mat4 getModelMatrix();

	/* Resets particle's data to defaults. */
	void reset(unsigned int programTime);

private:
	/* Doesn't make sense to create an "empty" particle, so we keep this private. */
    Particle();

	/*
	 * Initialises the new Particle.
	 * @param	position	The position at which the particle will be initialised.
	 * @param	colour		The colour of the particle.
	 * @param	speed	The speed at which the particle is travelling.
	 * @param	programTime	The current time of the program. Used for checking by the ParticleGenerator regarding how long the particle has been alive, and thus whether it should be deleted.
	 * @param	indicesOffset An offset of the indices, relative to the object's position in the buffer.
	 */
    void particleInit(glm::vec3 position, glm::vec4 colour, float speed, unsigned int programTime, unsigned int indicesOffset = 0);

	/* Calculates the model matrix. */
	void calcModelMatrix();

	
	glm::vec3 mInitPos;
	glm::vec3 mPosition; // position of the particle
	glm::vec4 mColour; // the particle's colour
	float mSpeed; // the speed at which the particle is travelling.
	unsigned int mBirthTime; // the program time at which the particle was crated.

	glm::mat4 mModelMatrix; // the particle's model matrix

	std::vector<float> mVertices; // the vertex data for the particle
	std::vector<unsigned int> mIndices; // the index data for the particle
};


#endif
