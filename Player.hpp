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
	/* Basic Player constructor.
	 * @param	programID	The shader program to which Player data will be rendered.
	 */
    Player(int programID);
	/* More advanced Player constructor.
	 * @param	programID	The shader program to which Player data will be rendered.
	 * @param	objfile		Filename associated with an OBJ file, from which data will be read.
	 */
    Player(int programID, const char* objfile);
	/* Advanced Player constructor.
	 * @param	programID	The shader program to which Player data will be rendered.
	 * @param	objfile		Filename associated with an OBJ file, from which data will be read.
	 * @param	rotate		Amount by which the Player will be rotated, in the x, y and z planes
	 * @param	translate	Translation amount of the Player (ie its position).
	 * @param	scale		Amount by which the Player will be scaled.
	 */
    Player(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale);
	/* Basic Player destructor. */
    ~Player();

	/* Movement & rotation functions, for ease of input. */
    void strafeLeft();
    void strafeRight();
    void moveForward();
    void moveBackward();
    void rotLeft();
    void rotRight();

	/* Return the Player to its previous position. */
    void setPrevPos();

    /* Stop all player movement. */
    void stopMovement();
    /* Idle player momentum. */
    void idleMovement();
    /* Check for object collision */
    bool checkCollision(bool collisionOn, std::vector<Object> objects);

private:
    static const float PLAYER_SPEED = 0.3f; // speed of the Player's movement.
    static const float IDLE_SPEED = 0.1f; // idle movement Player speed
    glm::vec3 prevTranslation; // previous position of the Player.
    glm::vec3 prevRotation; // previous rotation of the Player.

    glm::vec3 idleTranslation;
    glm::vec3 idleRotation;
};


#endif
