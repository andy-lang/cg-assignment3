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
	 * @param	rotation	The rotation of the particle in the x, y and z planes.
	 * @param	colour		The colour of the particle.
	 * @param	speed	The speed at which the particle is travelling.
	 * @param	programTime	The current time of the program. Used for checking by the ParticleGenerator regarding how long the particle has been alive, and thus whether it should be deleted.
	 * @param	indicesOffset An offset of the indices, relative to the object's position in the ParticleGenerator buffer.
	 * @param	timeToLive	Program time, in milliseconds, until the particle will be reset to its initial position.
	 */
    Particle(glm::vec3 position, glm::vec3 rotation, glm::vec4 colour, float speed, unsigned int programTime, unsigned int indicesOffset = 0, unsigned int timeToLive = 2000);
    ~Particle();

	/* Returns the program time at which the Particle was created or last reset. */
	unsigned int getBirthTime() const;
	/* Set the time at which the Particle was created or last reset. */
	void setBirthTime(unsigned int birthTime);
	/* Returns the number of milliseconds that the Particle will continue moving until being reset. */
	unsigned int getTimeToLive() const;

	/* Returns the vertex data of the Particle. */
	std::vector<float> getVertexData() const;
	/* Returns the index data of the Particle. */
	std::vector<unsigned int> getIndexData() const;
	/* Returns the colour of the particle. */
	glm::vec4 getColour();

	/* Returns the number of vertices that the Particle has. */
	unsigned int getVerticesSize() const;
	/* Returns the number of indices that the Particle has. */
	unsigned int getIndicesSize() const;

	/* Updates the model matrix, relative to the Particle's properties (eg position, speed, etc), then returns this model matrix. */
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
	 * @param	rotation	The rotation of the particle in the x, y and z planes.
	 * @param	colour		The colour of the particle.
	 * @param	speed	The speed at which the particle is travelling.
	 * @param	programTime	The current time of the program. Used for checking by the ParticleGenerator regarding how long the particle has been alive, and thus whether it should be deleted.
	 * @param	indicesOffset An offset of the indices, relative to the object's position in the ParticleGenerator buffer.
	 * @param	timeToLive	Program time, in milliseconds, until the particle will be reset to its initial position.
	 */
    void particleInit(glm::vec3 position, glm::vec3 rotation, glm::vec4 colour, float speed, unsigned int programTime, unsigned int indicesOffset = 0, unsigned int timeToLive = 2000);

	/* Calculates the model matrix. */
	void calcModelMatrix();

	
	glm::vec3 mInitPos; // position at which the Particle was initialised
	glm::vec3 mPosition; // position of the Particle
	glm::vec3 mRotation; // rotation in x,y,z planes
	glm::vec4 mColour; // the Particle's colour
	float mSpeed; // the speed at which the Particle is travelling.
	unsigned int mBirthTime; // the program time at which the Particle was created, in milliseconds.
	unsigned int mTimeToLive; // time between resets of Particle's position etc.

	glm::mat4 mModelMatrix; // the particle's model matrix

	std::vector<float> mVertices; // the vertex data for the particle
	std::vector<unsigned int> mIndices; // the index data for the particle
};

#endif
