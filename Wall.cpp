#include "Wall.hpp"

Wall::Wall(int programID) {
    //?? TODO: stub
}

Wall::Wall(int programID, const char* objfile) {
    objectInit(programID, objfile, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
}

Wall::Wall(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale) {
    objectInit(programID, objfile, rotate, translate, scale);
}

Wall::~Wall() {
    //?? TODO: stub
}