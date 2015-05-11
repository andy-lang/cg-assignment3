#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include "Object.hpp"
#include <iostream>

class Player : public Object {
public:
    Player(int programID);
    Player(int programID, const char* objfile);
    Player(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale);
    ~Player();

    void moveLeft();
    void moveRight();
    void moveForward();
    void moveBackward();

private:
    static const float PLAYER_SPEED = 0.5f;

};


#endif
