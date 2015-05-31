#include "Player.hpp"
#include <math.h>

Player::Player(int programID) {
    //?? TODO: stub
}

Player::Player(int programID, const char* objfile){
    objectInit(programID, objfile, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
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
	glm::vec3 prevCoord = glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z);
	setTranslation(glm::vec3(mTranslate.x + (sin(mRotate.y + (90.0*M_PI/180.0))*PLAYER_SPEED), mTranslate.y, mTranslate.z + (cos(mRotate.y + (90.0*M_PI/180.0))*PLAYER_SPEED)));
}

void Player::strafeRight(){
	setTranslation(glm::vec3(mTranslate.x + (sin(mRotate.y - (90.0*M_PI/180.0))*PLAYER_SPEED), mTranslate.y, mTranslate.z + (cos(mRotate.y - (90.0*M_PI/180.0))*PLAYER_SPEED)));
}

void Player::rotLeft() {
    setRotation(glm::vec3(mRotate.x, mRotate.y+0.04, mRotate.z));
}

void Player::rotRight() {
    setRotation(glm::vec3(mRotate.x, mRotate.y-0.04, mRotate.z));
}

void Player::moveForward() {
    setTranslation(glm::vec3(mTranslate.x + (sin(mRotate.y)*PLAYER_SPEED), mTranslate.y, mTranslate.z + (cos(mRotate.y)*PLAYER_SPEED)));
}

void Player::moveBackward() {
    setTranslation(glm::vec3(mTranslate.x - (sin(mRotate.y)*PLAYER_SPEED), mTranslate.y, mTranslate.z - (cos(mRotate.y)*PLAYER_SPEED)));
}