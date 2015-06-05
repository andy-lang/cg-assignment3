/**********************************************************************
 * Object to generate a set number of particles, and simulate a particular particle-like effect.
 *
 * @author	:	Andrew Lang
 * @id		:	a1648205
 * @created :	2015-06-03
 * @project	:	CG assignment 3
**********************************************************************/

#ifndef PARTICLEGENERATOR_HPP
#define PARTICLEGENERATOR_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "external_files/soil/src/SOIL.h"
#include "external_files/tiny_obj_loader/tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include "Particle.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

class ParticleGenerator {
public:
	/* Basic ParticleGenerator constructor. */
    ParticleGenerator();
	/* Advanced ParticleGenerator constructor.
	 * @param	programID	The ID of the GLSL shader program to which the particles will be rendered.
	 * @param	position	Position of the generator in the world.
	 * @param	rotation	Rotation of the generator.
	 * @param	programTime	The current 'system' time of the program. Used for randomisation and resetting of positions.
	 */
    ParticleGenerator(unsigned int programID, glm::vec3 position, glm::vec3 rotation, unsigned int programTime);
	/* Basic ParticleGenerator destructor. */
    ~ParticleGenerator();

	/* Render all particles associated with this generator.
	 * @param	programID	The ID of the GLSL shader program to which the particles will be rendered.
	 * @param	programTime	The current 'system' time of the program. Used for randomisation and resetting of positions.
	 */
	void render(unsigned int programID, unsigned int programTime);

private:
	/* Initialise the generator and the particles contained within it.
	 * @param	programID	The ID of the GLSL shader program to which the particles will be rendered.
	 * @param	position	Position of the generator in the world.
	 * @param	rotation	Rotation of the generator.
	 * @param	programTime	The current 'system' time of the program. Used for randomisation and resetting of positions.
	 */
	void initGenerator(unsigned int programID, glm::vec3 position, glm::vec3 rotation, unsigned int programTime);

	/* Generate a random float between two values. */
	float randomFloat(float a, float b);

	glm::vec3 mPosition; // position of the generator in the world.

	std::vector<Particle> mParticles; // list of all particles
	unsigned int mVerticesSize; // total number of vertices between all particles
	unsigned int mIndicesSize; // total number of indices between all particles

	static const unsigned int mBufSize = 2;
	unsigned int mBuffer[mBufSize];
	static const unsigned int VERTICES_BUF_POS = 0;
	static const unsigned int INDICES_BUF_POS = 1;
	unsigned int mVertexVaoHandle;
};


#endif
