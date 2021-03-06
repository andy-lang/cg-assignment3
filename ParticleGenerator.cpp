#include "ParticleGenerator.hpp"

ParticleGenerator::ParticleGenerator() {
	//?? TODO: stub
}

ParticleGenerator::ParticleGenerator(unsigned int programID, glm::vec3 position, glm::vec3 rotation, unsigned int programTime) {
	initGenerator(programID, position, rotation, programTime);
}

ParticleGenerator::~ParticleGenerator() {
	//?? TODO: stub
}

void ParticleGenerator::initGenerator(unsigned int programID, glm::vec3 position, glm::vec3 rotation, unsigned int programTime) {
	glUseProgram(programID);

	mPosition = position;

	mVerticesSize = 0;
	mIndicesSize = 0;

	// create flame particles
	unsigned int NUM_FLAME_PARTICLES = (unsigned int)randomFloat(20, 50);
	unsigned int indicesOffset = 0;
	for (int i = 0; i < NUM_FLAME_PARTICLES; i++) {
		float xPosVar = randomFloat(-0.03, 0.03);
		float zPosVar = randomFloat(-0.03, 0.03);
		float speedVar= randomFloat(-0.001, 0.0008);
		float timeToLiveVar = randomFloat(1000, 3000);
		float colourVar = randomFloat(0.0, 1.0);

		glm::vec4 colour;
		float alpha = randomFloat(0.7, 1.0);
		if (colourVar < 0.78f) {
			// create red/orange particles
			float r = randomFloat(0.95, 1.0f);
			float g = randomFloat(0.0f, 0.2f);
			colour = glm::vec4(r, g, 0.0f, alpha);
		}
		else {
			// else create yellow
			float r = randomFloat(0.85, 1.0f);
			colour = glm::vec4(r, r, 0.0f, alpha);
		}

	    Particle p(mPosition + glm::vec3(xPosVar, 0.0f, zPosVar), rotation, colour, 0.0013f+speedVar, programTime, indicesOffset, timeToLiveVar);
		mParticles.push_back(p);

		indicesOffset += p.getVerticesSize()/VALS_PER_VERT;

		mVerticesSize += p.getVerticesSize();
		mIndicesSize += p.getIndicesSize();
	}


	// create smoke particles
	unsigned int NUM_SMOKE_PARTICLES = (unsigned int)randomFloat(10,15);
	for (int idx = 0; idx < NUM_SMOKE_PARTICLES; idx++) {
		float xPosVar = randomFloat(-0.03, 0.03);
		float zPosVar = randomFloat(-0.03, 0.05);
		float speedVar= randomFloat(-0.001, 0.001);
		float timeVar = randomFloat(0, 1000);
		float timeToLiveVar = randomFloat(1000, 3000);

		float grey = randomFloat(0.0, 0.06);

		glm::vec4 colour = glm::vec4(grey, grey, grey, 1.0f-grey);


	    Particle p(mPosition + glm::vec3(xPosVar, 0.0f, zPosVar), rotation, colour, 0.0025f+speedVar, programTime+timeVar, indicesOffset, timeToLiveVar);
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

void ParticleGenerator::render(unsigned int programID, unsigned int programTime) {
	for (int i = 0; i < mParticles.size(); i++) {
	    if (programTime-mParticles.at(i).getBirthTime() >= mParticles.at(i).getTimeToLive()) {
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
	unsigned int offset = 0;
	for (int i = 0; i < mParticles.size(); i++) {
		glUniformMatrix4fv(modelHandle, 1, false, glm::value_ptr(mParticles.at(i).updateModelMatrix()));
		glUniform4fv(colourHandle, 1, glm::value_ptr(mParticles.at(i).getColour()));

		glDrawRangeElements(GL_TRIANGLES, offset, offset + (mParticles.at(i).getVerticesSize()/VALS_PER_VERT), mParticles.at(i).getIndicesSize(), GL_UNSIGNED_INT, 0);
		offset += mParticles.at(i).getVerticesSize()/VALS_PER_VERT;
	}

	glBindVertexArray(0);
}

// Lovingly borrowed from http://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats 
float ParticleGenerator::randomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	return (random * (b-a)) + a;
}
