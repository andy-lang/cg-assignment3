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

void Camera::render(int programID) {
    int viewHandle = glGetUniformLocation(programID, "view_matrix");
    if (viewHandle == -1) {
        std::cerr << "Could not find uniform variable 'view_matrix'" << std::endl;
        exit(1);
    }

    mViewMatrix = glm::mat4(); // reset view matrix
    if (mObj == NULL) {
        // for the time being, if the camera isn't attached to anything, put it at a static position.
        mViewMatrix = glm::lookAt(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    else {
        mViewMatrix = glm::lookAt(mObj->getTranslation()+mTranslate, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        std::cout << "obj position = " << mObj->getTranslation().x << ", " << mObj->getTranslation().y << ", " << mObj->getTranslation().z << std::endl;
        std::cout << "so total position = " << (mObj->getTranslation()+mTranslate).x << ", " << (mObj->getTranslation()+mTranslate).y << ", " << (mObj->getTranslation()+mTranslate).z << std::endl;
    }

    glUniformMatrix4fv(viewHandle, 1, false, glm::value_ptr(mViewMatrix));

}
