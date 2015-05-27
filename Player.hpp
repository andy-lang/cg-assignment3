/**********************************************************************
 * Derivative class of Object, representing a movable Player.
 * Thus this class contains a number of methods related to functionality of a Player, such as movement control.
 * Attach an instance of this class to the Camera, and you can have control over a Player and a Camera that moves with it.
 *
 * @author 	: Andrew Lang
 * @id 		: a1648205
 * @created 	: 2015-05-11
 * @project 	: CG Assignment 3
**********************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "external_files/tiny_obj_loader/tiny_obj_loader.h"

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
