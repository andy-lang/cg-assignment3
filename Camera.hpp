#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/glut.h>

#include "libs/Lib.h"
#include "Object.hpp"
#include <iostream>

class Camera {
public:
    Camera();
    ~Camera();

    void attachToObject(Object* obj);
    void attachToObject(Object* obj, glm::vec3 translate);
private:
    Object* mObj;
    glm::vec3 mTranslate;
    glm::mat4 mViewMatrix;

};

#endif
