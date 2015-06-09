#include "Enemy.hpp"
#include <math.h>

Enemy::Enemy(int programID) {
    //?? TODO: stub
}

Enemy::Enemy(int programID, const char* objfile){
    objectInit(programID, objfile, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
    prevTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
    prevRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    BOUNCE_SPEED = -0.1f;
    translationDirection = true;
}

Enemy::Enemy(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale){
    objectInit(programID, objfile, rotate, translate, scale);
    prevTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
    prevRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    BOUNCE_SPEED = -0.1f;
    translationDirection = true;
}

Enemy::~Enemy() {
    //?? TODO: stub
}

void Enemy::update(bool collisionOn, std::vector<Object> objects){
	if(mTranslate.y < -0.23){
		BOUNCE_SPEED = 0.05f;
	}
	else if(mTranslate.y > 0.0){
		BOUNCE_SPEED = -0.05f;
	}

	if(translationDirection){
		prevTranslation = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
		setTranslation(glm::vec3(mTranslate.x + SPEED, mTranslate.y + BOUNCE_SPEED, mTranslate.z));
	}
	else{
		prevTranslation = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
		setTranslation(glm::vec3(mTranslate.x - SPEED, mTranslate.y + BOUNCE_SPEED, mTranslate.z));
	}

	if(checkCollision(collisionOn, objects)){
		switchDirection();
		setPrevPos();
	}
}

void Enemy::setPrevPos(){
	setTranslation(prevTranslation);
	setRotation(prevRotation);

	stopMovement();
}
    
void Enemy::stopMovement(){
	setTranslation(glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z));
	setRotation(glm::vec3(mRotate.x, mRotate.y, mRotate.z));
}

void Enemy::switchDirection(){
	if(translationDirection){
		translationDirection = false;
		setRotation(glm::vec3(mRotate.x, mRotate.y + M_PI, mRotate.z));
	}
	else{
		translationDirection = true;
		setRotation(glm::vec3(mRotate.x, mRotate.y + M_PI, mRotate.z));
	}
}
    
bool Enemy::checkCollision(bool collisionOn, std::vector<Object> objects){
	bool collisionDetected = false;
	glm::vec3 objTranslation;
	glm::vec3 playerTranslation;

	for (int j = 0; j < objects.size(); j++) {
		// Currently just checking collision with walls
		if ((collisionOn == true) && (j < 36)){
			objTranslation = objects.at(j).getTranslation();
			playerTranslation = getTranslation();

			//Get the absolute x and z differences (sides of triangle)
			float xDiff = std::abs(playerTranslation.x - objTranslation.x);
			float zDiff = std::abs(playerTranslation.z - objTranslation.z);

			//Calculate the absolute distance between the center of the player and object
			float absDist = std::sqrt(std::pow(xDiff, 2.0) + std::pow(zDiff, 2.0));
			//Get the internal angle
			float angle = std::atan2(zDiff, xDiff);

			float internalObjDist;
			float internalPlayerDist;

			/*Determine which quadrant the player is in relation to the object
			  This is on a xz plane											  */
			if(std::abs(angle) <= M_PI/4.0){
				// The left or right quad (equivalent cases)
				//Calcualte the internal distances within the square and player
				internalObjDist = std::abs((0.5)/(std::cos(angle)));
				internalPlayerDist = std::abs(std::sqrt(pow(0.3, 2) +  pow(0.3, 2)));
			}
			else{
				// The top or bottom quad (equivalent cases)
				//Switch the angle of reference
				angle = M_PI/2.0 - angle;
				internalObjDist = std::abs((0.5)/(std::cos(angle)));
				internalPlayerDist = std::abs(std::sqrt(pow(0.3, 2) +  pow(0.3, 2)));
			}

			//If the distance is less than 0 must have a collision
			if((absDist - internalObjDist - internalPlayerDist) < 0){
				collisionDetected = true;
			}
		}

        if(collisionDetected){
            return true;
        }
	}
	return false;
}