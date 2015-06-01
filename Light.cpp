#include "Light.hpp"

Light::Light() {
	//?? TODO: stub
}

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	setPosition(position);
	setAmbient(ambient);
	setDiffuse(diffuse);
	setSpecular(specular);
}

Light::~Light() {
	//?? TODO: stub
}

glm::vec3 Light::getPosition() {
	return mPosition;
}

glm::vec3 Light::getAmbient() {
	return mAmbient;
}

glm::vec3 Light::getDiffuse() {
	return mDiffuse;
}

glm::vec3 Light::getSpecular() {
	return mSpecular;
}

void Light::setPosition(glm::vec3 position) {
	mPosition = position;
}

void Light::setAmbient(glm::vec3 ambient) {
	mAmbient = ambient;
}

void Light::setDiffuse(glm::vec3 diffuse) {
	mDiffuse = diffuse;
}

void Light::setSpecular(glm::vec3 specular) {
	mSpecular = specular;
}
