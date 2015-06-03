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
	glUseProgram(programID);

	mPosition = position;

	mVerticesSize = 0;
	mIndicesSize = 0;

	for (int i = 0; i < 3; i++) {
		std::cout << mPosition[i] << " ";
	}
	std::cout << std::endl;


	// create individual particles
	glm::vec4 orange = glm::vec4(1.0f, 0.3f, 0.0f, 1.0f);
	unsigned int indicesOffset = 0;

	for (int i = 0; i < NUM_PARTICLES; i++) {
	    Particle p(mPosition, orange, 0.002f, programTime, indicesOffset);
		mParticles.push_back(p);

		for (int j = 0; j < mParticles.at(i).getIndicesSize(); j++) {
		    std::cout << mParticles.at(i).getIndexData().at(j) << " ";
		}
		std::cout << std::endl;
		indicesOffset += p.getVerticesSize()/VALS_PER_VERT;

		mVerticesSize += p.getVerticesSize();
		mIndicesSize += p.getIndicesSize();
	}
	std::cout << "mParticles size = " << mParticles.size() << std::endl;
	std::cout << "mVerticesSize = " << mVerticesSize << ", mIndicesSize = " << mIndicesSize << std::endl;

	glGenBuffers(mBufSize, mBuffer);

	glGenVertexArrays(1, &mVertexVaoHandle);
	glBindVertexArray(mVertexVaoHandle);

	int vertLoc = glGetAttribLocation(programID, "a_vertex");

	// buffer vertices
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer[VERTICES_BUF_POS]);
	//glBufferData(GL_ARRAY_BUFFER, mVerticesSize*sizeof(float), 0, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, mParticles.at(0).getVerticesSize()*sizeof(float), &mParticles.at(0).getVertexData().front(), GL_STATIC_DRAW);
	unsigned int offset = 0;
	/*
	for (int i = 0; i < mParticles.size(); i++) {
	    glBufferSubData(GL_ARRAY_BUFFER, offset*sizeof(float), mParticles.at(i).getVerticesSize()*sizeof(float), &mParticles.at(i).getVertexData().front());
		offset += mParticles.at(i).getVerticesSize();
	}
	*/
	glEnableVertexAttribArray(vertLoc);
	glVertexAttribPointer(vertLoc, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);

	// buffer indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer[INDICES_BUF_POS]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mParticles.at(0).getIndicesSize()*sizeof(unsigned int), &mParticles.at(0).getIndexData().front(), GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesSize*sizeof(unsigned int), 0, GL_STATIC_DRAW);
	offset = 0;

	/*
	for (int i = 0; i < mParticles.size(); i++) {
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset*sizeof(unsigned int), mParticles.at(i).getIndicesSize()*sizeof(unsigned int), &mParticles.at(i).getIndexData().front());
		offset += mParticles.at(i).getIndicesSize();
	}
	*/

	// unbind vertex array
	glBindVertexArray(0);
	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// and we're done!
}

void ParticleGenerator::render(unsigned int programID, unsigned int programTime) {
	for (int i = 0; i < mParticles.size(); i++) {
	    if (programTime-mParticles.at(i).getBirthTime() >= PARTICLE_TIME_TO_LIVE) {
			std::cout << "particle " << i << " reset" << std::endl;
			mParticles.at(i).reset(programTime);
	    }
	}


	glUseProgram(programID);

	int colourHandle = glGetUniformLocation(programID, "a_colour");
	if (colourHandle == -1) {
		std::cerr << "Could not find uniform variable 'a_colour'" << std::endl;
		exit(1);
	}

	int modelHandle = glGetUniformLocation(programID, "model_matrix");
	if (modelHandle == -1) {
		std::cerr << "Could not find uniform variable 'model_matrix'" << std::endl;
		exit(1);
	}

	glBindVertexArray(mVertexVaoHandle);
	/*
	unsigned int offset = 0;
	for (int i = 0; i < mParticles.size(); i++) {
		glUniformMatrix4fv(modelHandle, 1, false, glm::value_ptr(mParticles.at(i).updateModelMatrix()));
		glUniform4fv(colourHandle, 1, glm::value_ptr(mParticles.at(i).getColour()));

		//glDrawRangeElements(GL_TRIANGLES, offset, offset + (mParticles.at(i).getVerticesSize()/VALS_PER_VERT), mParticles.at(i).getIndicesSize(), GL_UNSIGNED_INT, 0);
	}
	*/
	glUniformMatrix4fv(modelHandle, 1, false, glm::value_ptr(mParticles.at(0).updateModelMatrix()));
	glUniform4fv(colourHandle, 1, glm::value_ptr(mParticles.at(0).getColour()));
	glm::vec4 colour = mParticles.at(0).getColour();
	

	glDrawElements(GL_TRIANGLES, mParticles.at(0).getIndicesSize(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
