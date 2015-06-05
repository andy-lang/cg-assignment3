/**********************************************************************
 * Derivative class of Object, representing a moving Enemy.
 * This class contains the enemy AI which control its movement and actions
 *
 * @author 	: Gavin Meredith
 * @id 		: a1645739
 * @created 	: 2015-06-05
 * @project 	: CG Assignment 3
**********************************************************************/

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "external_files/tiny_obj_loader/tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include "Object.hpp"
#include <iostream>

class Enemy : public Object {
public:
	/* Basic Enemy constructor.
	 * @param	programID	The shader program to which Enemy data will be rendered.
	 */
    Enemy(int programID);
	/* More advanced Enemy constructor.
	 * @param	programID	The shader program to which Enemy data will be rendered.
	 * @param	objfile		Filename associated with an OBJ file, from which data will be read.
	 */
    Enemy(int programID, const char* objfile);
	/* Advanced Enemy constructor.
	 * @param	programID	The shader program to which Enemy data will be rendered.
	 * @param	objfile		Filename associated with an OBJ file, from which data will be read.
	 * @param	rotate		Amount by which the Enemy will be rotated, in the x, y and z planes
	 * @param	translate	Translation amount of the Enemy (ie its position).
	 * @param	scale		Amount by which the Enemy will be scaled.
	 */
    Enemy(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale);
	/* Basic Enemy destructor. */
    ~Enemy();

	/* Movement & rotation functions */

	/* Return the Enemy to its previous position. */
    void setPrevPos();

private:
    static const float PLAYER_SPEED = 0.4f; // speed of the Enemy's movement.
    glm::vec3 prevTranslation; // previous position of the Enemy.
    glm::vec3 prevRotation; // previous rotation of the Enemy.
};


#endif
