#include "Particle.hpp"

Particle::Particle() {
	//?? TODO: stub
}

Particle::Particle(glm::vec3 position, glm::vec3 rotation, glm::vec4 colour, float speed, unsigned int programTime, unsigned int indicesOffset, unsigned int timeToLive) {
	particleInit(position, rotation, colour, speed, programTime, indicesOffset, timeToLive);
}

Particle::~Particle() {
	//?? TODO: stub
}

unsigned int Particle::getBirthTime() const {
	return mBirthTime;
}

void Particle::setBirthTime(unsigned int birthTime) {
	mBirthTime = birthTime;
}

unsigned int Particle::getTimeToLive() const {
	return mTimeToLive;
}

std::vector<float> Particle::getVertexData() const {
	return mVertices;
}

std::vector<unsigned int> Particle::getIndexData() const {
	return mIndices;
}

unsigned int Particle::getVerticesSize() const {
	return mVertices.size();
}

unsigned int Particle::getIndicesSize() const {
	return mIndices.size();
}

glm::vec4 Particle::getColour() {
	return mColour;
}

glm::mat4 Particle::updateModelMatrix() {
	mPosition.y += mSpeed;
	return getModelMatrix();
}

glm::mat4 Particle::getModelMatrix() {
	calcModelMatrix();
	return mModelMatrix;
}

void Particle::reset(unsigned int programTime) {
	mPosition = mInitPos;
	mBirthTime = programTime;
	calcModelMatrix();
}

void Particle::particleInit(glm::vec3 position, glm::vec3 rotation, glm::vec4 colour, float speed, unsigned int programTime, unsigned int indicesOffset, unsigned int timeToLive) {
	mPosition = position;
	mRotation = rotation;
	mInitPos = position;
	mColour = colour;
	mSpeed = speed;
	mBirthTime = programTime;
	mTimeToLive = timeToLive;

	
	// create vertices to make a square
	// top left square
	mVertices.push_back(-1.0f);
	mVertices.push_back(-1.0f);
	mVertices.push_back(0.0f);

	// top right square
	mVertices.push_back(1.0f);
	mVertices.push_back(-1.0f);
	mVertices.push_back(0.0f);

	// bottom left square
	mVertices.push_back(-1.0f);
	mVertices.push_back(1.0f);
	mVertices.push_back(0.0f);

	// bottom right square
	mVertices.push_back(1.0f);
	mVertices.push_back(1.0f);
	mVertices.push_back(0.0f);

	// and connect the vertices to indices
	mIndices.push_back(0 + indicesOffset);
	mIndices.push_back(1 + indicesOffset);
	mIndices.push_back(2 + indicesOffset);

	mIndices.push_back(1 + indicesOffset);
	mIndices.push_back(2 + indicesOffset);
	mIndices.push_back(3 + indicesOffset);

	calcModelMatrix();
}

void Particle::calcModelMatrix() {
	mModelMatrix = glm::mat4();
	mModelMatrix = glm::translate(mModelMatrix, mPosition);
	mModelMatrix = glm::scale(mModelMatrix, glm::vec3(0.012f, 0.012f, 0.012f));
	mModelMatrix = glm::rotate(mModelMatrix, mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	mModelMatrix = glm::rotate(mModelMatrix, mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	mModelMatrix = glm::rotate(mModelMatrix, mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
}
