#include "Player.hpp"
#include <math.h>

Player::Player(int programID) {
    //?? TODO: stub
}

Player::Player(int programID, const char* objfile){
    objectInit(programID, objfile, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
    prevTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
    prevRotation = glm::vec3(0.0f, 0.0f, 0.0f);

    idleTranslation = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
    idleRotation = glm::vec3(mRotate.x, mRotate.y, mRotate.z);
}

Player::Player(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale){
    objectInit(programID, objfile, rotate, translate, scale);
}

Player::~Player() {
    //?? TODO: stub
}

void Player::strafeLeft(){
	prevTranslation = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
	idleTranslation = glm::vec3(mTranslate.x + (sin(mRotate.y + (90.0*M_PI/180.0))*IDLE_SPEED), mTranslate.y, mTranslate.z + (cos(mRotate.y + (90.0*M_PI/180.0))*IDLE_SPEED));
	idleRotation = glm::vec3(mRotate.x, mRotate.y, mRotate.z);

	setTranslation(glm::vec3(mTranslate.x + (sin(mRotate.y + (90.0*M_PI/180.0))*PLAYER_SPEED), mTranslate.y, mTranslate.z + (cos(mRotate.y + (90.0*M_PI/180.0))*PLAYER_SPEED)));
}

void Player::strafeRight(){
	prevTranslation = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
	idleTranslation = glm::vec3(mTranslate.x + (sin(mRotate.y - (90.0*M_PI/180.0))*IDLE_SPEED), mTranslate.y, mTranslate.z + (cos(mRotate.y - (90.0*M_PI/180.0))*IDLE_SPEED));
	idleRotation = glm::vec3(mRotate.x, mRotate.y, mRotate.z);

	setTranslation(glm::vec3(mTranslate.x + (sin(mRotate.y - (90.0*M_PI/180.0))*PLAYER_SPEED), mTranslate.y, mTranslate.z + (cos(mRotate.y - (90.0*M_PI/180.0))*PLAYER_SPEED)));
}

void Player::rotLeft() {
	prevRotation = glm::vec3(mRotate.x, mRotate.y, mRotate.z);
	idleTranslation = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
	idleRotation = glm::vec3(mRotate.x, mRotate.y+0.05, mRotate.z);

    setRotation(glm::vec3(mRotate.x, mRotate.y+0.1, mRotate.z));
}

void Player::rotRight() {
	prevRotation = glm::vec3(mRotate.x, mRotate.y, mRotate.z);
	idleTranslation = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
	idleRotation = glm::vec3(mRotate.x, mRotate.y-0.05, mRotate.z);

    setRotation(glm::vec3(mRotate.x, mRotate.y-0.1, mRotate.z));
}

void Player::moveForward() {
	prevTranslation = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
	idleTranslation = glm::vec3(mTranslate.x + (sin(mRotate.y)*IDLE_SPEED), mTranslate.y, mTranslate.z + (cos(mRotate.y)*IDLE_SPEED));
	idleRotation = glm::vec3(mRotate.x, mRotate.y, mRotate.z);

    setTranslation(glm::vec3(mTranslate.x + (sin(mRotate.y)*PLAYER_SPEED), mTranslate.y, mTranslate.z + (cos(mRotate.y)*PLAYER_SPEED)));
}

void Player::moveBackward() {
	prevTranslation = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
	idleTranslation = glm::vec3(mTranslate.x - (sin(mRotate.y)*IDLE_SPEED), mTranslate.y, mTranslate.z - (cos(mRotate.y)*IDLE_SPEED));
	idleRotation = glm::vec3(mRotate.x, mRotate.y, mRotate.z);

    setTranslation(glm::vec3(mTranslate.x - (sin(mRotate.y)*PLAYER_SPEED), mTranslate.y, mTranslate.z - (cos(mRotate.y)*PLAYER_SPEED)));
}

void Player::setPrevPos(){
	setTranslation(prevTranslation);
	setRotation(prevRotation);
}

void Player::stopMovement(){
	setTranslation(glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z));
	setRotation(glm::vec3(mRotate.x, mRotate.y, mRotate.z));
}

void Player::idleMovement(){
	setTranslation(idleTranslation);
	setRotation(idleRotation);
}

bool Player::checkCollision(bool collisionOn, std::vector<Object> objects){

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