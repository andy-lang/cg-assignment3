#include "Enemy.hpp"
#include <math.h>

Enemy::Enemy(int programID) {
    //?? TODO: stub
}

Enemy::Enemy(int programID, const char* objfile){
    objectInit(programID, objfile, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
}

Enemy::Enemy(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale){
    objectInit(programID, objfile, rotate, translate, scale);
}

Enemy::~Enemy() {
    //?? TODO: stub
}