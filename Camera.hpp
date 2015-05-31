/**********************************************************************
 * Class that controls the view matrix for the program.
 * Camera can either be fixed at a particular location (stationary), or attached to a particular Object.
 *
 * @author 	: Andrew Lang
 * @id 		: a1648205
 * @created 	: 2015-05-10
 * @project 	: CG Assignment 3
**********************************************************************/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"
#include "external_files/glm/glm/gtx/rotate_vector.hpp"

#include <GL/glut.h>

#include "libs/Lib.h"
#include "Object.hpp"

#include <iostream>
#include <cstdlib>

class Camera {
public:
    /* Basic Camera constructor. */
    Camera();
    /* Basic Camera destructor. */
    ~Camera();

    /* Sets the Camera so that its movement is attached to a particular Object. Thus when the Object moves the Camera moves with it. 
     * @param   obj     The object to which the Camera will be attached. */
    void attachToObject(Object* obj);

    /* More advanced version of above function.
     * This version of the method allows for a translation to take place, so that the Camera can look somewhere relative to an Object.
     * Useful for third person mode, etc.
     * @param   obj     The object to which the Camera will be attached.
     * @param   translate The translation vector for the Camera's placement.
     */
    void attachToObject(Object* obj, glm::vec3 translate);

    /* Returns the object to which the Camera is attached, or NULL if no such object exists. */
    Object* getAttachedObject() const;

    /* "Renders" the camera.
     * In essence all this does is recalculate the view matrix, then send it to the specified shader program.
     * @param   programID   The shader program to which the Camera will be "rendered".
     */
    void render(int programID);

private:
    Object* mObj;
    glm::vec3 mTranslate;
    glm::mat4 mViewMatrix;

};

#endif
