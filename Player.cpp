#include "Player.hpp"

Player::Player(int programID) {
    //?? TODO: stub
}

Player::Player(int programID, const char* objfile) {
    objectInit(programID, objfile, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
}

Player::Player(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale) {
    objectInit(programID, objfile, rotate, translate, scale);
}

Player::~Player() {
    //?? TODO: stub
}

void Player::moveLeft() {
    setTranslation(glm::vec3(mTranslate.x+PLAYER_SPEED, mTranslate.y, mTranslate.z));
}

void Player::moveRight() {
    setTranslation(glm::vec3(mTranslate.x-PLAYER_SPEED, mTranslate.y, mTranslate.z));
}

void Player::moveForward() {
    setTranslation(glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z+PLAYER_SPEED));
}

void Player::moveBackward() {
    setTranslation(glm::vec3(mTranslate.x, mTranslate.y, mTranslate.z-PLAYER_SPEED));
}
