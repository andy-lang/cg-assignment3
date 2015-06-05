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

/**********************************************************************
 * Movement functionality
 *
 * @author 	: Gavin Meredith
 * @id 		: a1645739
**********************************************************************/
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