#include "Camera.hpp"

Camera::Camera() {
    // set member variables to default values.
    mObj = NULL;
    mTranslate = glm::vec3(0.0f, 0.0f, 0.0f); 
    mViewMatrix = glm::mat4();
}

Camera::~Camera() {
    //?? TODO: stub
}

void Camera::attachToObject(Object* obj) {
    mObj = obj;
    mTranslate = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Camera::attachToObject(Object* obj, glm::vec3 translate) {
    mObj = obj;
    mTranslate = translate;
}

Object* Camera::getAttachedObject() const {
    return mObj;
}

void Camera::render(int programID) {
    int viewHandle = glGetUniformLocation(programID, "view_matrix");
    if (viewHandle == -1) {
        std::cerr << "Could not find uniform variable 'view_matrix'" << std::endl;
        exit(1);
    }

	calcViewMatrix();

    glUniformMatrix4fv(viewHandle, 1, false, glm::value_ptr(mViewMatrix));
}

void Camera::calcViewMatrix() {
	mViewMatrix = glm::mat4(); // reset view matrix
    if (mObj == NULL) {
        // for the time being, if the camera isn't attached to anything, put it at a static position.
        mViewMatrix = glm::lookAt(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else {
		mViewMatrix = glm::translate(mObj->getModelMatrix(), mTranslate); // translate relative to the object's model matrix
		mViewMatrix = glm::rotate(mViewMatrix, 3.14f, glm::vec3(0.0f, 1.0f, 0.0f)); // rotate by pi. This makes sure it's facing the right direction
		mViewMatrix = glm::inverse(mViewMatrix); // apparently the thing to do with the view matrix is to set it as the inverse of the model matrix after you've applied transformations. ¯\_(ツ)_/¯
    }
}

glm::mat4 Camera::getViewMatrix() {
	calcViewMatrix();
	return mViewMatrix;
}

void Camera::setViewMatrix(glm::mat4 newVM) {
    mViewMatrix = newVM;
    return;
}
