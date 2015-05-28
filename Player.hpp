#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

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

    void strafeLeft();
    void strafeRight();
    void rotLeft();
    void rotRight();
    void moveForward();
    void moveBackward();

    void setInputState(int x, int y);
    void setCamAngle();

private:
    static const float PLAYER_SPEED = 0.5f;
};


#endif
