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
    ParticleGenerator();
    ParticleGenerator(unsigned int programID, glm::vec3 position, glm::vec3 rotation, unsigned int programTime);
    ~ParticleGenerator();

	void render(unsigned int programID, unsigned int programTime);

private:

	void initGenerator(unsigned int programID, glm::vec3 position, glm::vec3 rotation, unsigned int programTime);

	/* Generate a random float between two values. */
	float randomFloat(float a, float b);

	glm::vec3 mPosition;

	std::vector<Particle> mParticles;
	unsigned int mVerticesSize;
	unsigned int mIndicesSize;

	static const unsigned int mBufSize = 2;
	unsigned int mBuffer[mBufSize];
	static const unsigned int VERTICES_BUF_POS = 0;
	static const unsigned int INDICES_BUF_POS = 1;
	unsigned int mVertexVaoHandle;
};


#endif
