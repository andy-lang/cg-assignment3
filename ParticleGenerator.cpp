#include "ParticleGenerator.hpp"

ParticleGenerator::ParticleGenerator() {
	//?? TODO: stub
}

ParticleGenerator::ParticleGenerator(unsigned int programID, glm::vec3 position, unsigned int programTime) {
	initGenerator(programID, position, programTime);
}

ParticleGenerator::~ParticleGenerator() {
	//?? TODO: stub
}

void ParticleGenerator::initGenerator(unsigned int programID, glm::vec3 position, unsigned int programTime) {
	mPosition = position;

	mVerticesSize = 0;
	mIndicesSize = 0;

	// create individual particles
	glm::vec4 orange = glm::vec4(1.0f, 0.3f, 0.0f, 1.0f);
	unsigned int indicesOffset = 0;
	for (int i = 0; i < NUM_PARTICLES; i++) {
	    Particle p(mPosition, orange, 0.2f, programTime, indicesOffset);
		mParticles.push_back(p);
		indicesOffset += p.getVerticesSize()/VALS_PER_VERT;

		mVerticesSize += p.getVerticesSize();
		mIndicesSize += p.getIndicesSize();
	}

	glGenBuffers(mBufSize, mBuffer);

	glGenVertexArrays(1, &mVertexVaoHandle);
	glBindVertexArray(mVertexVaoHandle);

	int vertLoc = glGetAttribLocation(programID, "a_vertex");

	// buffer vertices
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer[VERTICES_BUF_POS]);
	glBufferData(GL_ARRAY_BUFFER, mVerticesSize*sizeof(float), 0, GL_STATIC_DRAW);
	unsigned int offset = 0;
	for (int i = 0; i < mParticles.size(); i++) {
	    glBufferSubData(GL_ARRAY_BUFFER, offset*sizeof(float), mParticles.at(i).getVerticesSize()*sizeof(float), &mParticles.at(i).getVertexData().front());
		offset += mParticles.at(i).getVerticesSize();
	}
	glEnableVertexAttribArray(vertLoc);
	glVertexAttribPointer(vertLoc, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);

	// buffer indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer[INDICES_BUF_POS]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesSize*sizeof(unsigned int), 0, GL_STATIC_DRAW);
	offset = 0;
	for (int i = 0; i < mParticles.size(); i++) {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset*sizeof(unsigned int), mParticles.at(i).getIndicesSize()*sizeof(unsigned int), &mParticles.at(i).getIndexData().front());
		offset += mParticles.at(i).getIndicesSize();
	}

	// unbind vertex array
	glBindVertexArray(0);
	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// and we're done!
}
