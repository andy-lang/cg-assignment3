#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include <iostream>
#include <sstream>
#include <vector>

class Object {
public:
    /* Basic Object constructor. 
     * @param   programID   The shader program to buffer the object data to. */
    Object(int programID);

    /** More complex Object constructor.
     * Takes in a filename corresponding to an OBJ file, which it reads in and sets up the necessary data.
     * All other parameters are set to sensibly default values.
     * @param   programID   The shader program to buffer the object data to.
     * @param   objfile     The filename of where the data of an OBJ file is stored. 
     */
    Object(int programID, const char* objfile);

    /** Advanced Object constructor.
     * Takes in a filename corresponding to an OBJ file, which it reads in and sets up the necessary data.
     * Also contains parameters for more advanced stuff, like scaling, translation, etc.
     * @param   programID   The shader program to buffer the object data to.
     * @param   objfile     The filename of where the data of an OBJ file is stored. 
     * @param   rotations   The amount in the x, y, and z planes that the object will be rotated by.
     * @param   translate The amount in the x, y, and z planes that the object will be translated, relative to the origin of the world.
     * @param   scaleFactor Amount to scale the object by, as a percentage of its original size. Defaults to its initial size if not specified.
     */
    Object(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scaleFactor);

    /* Basic Object destructor. */
    ~Object();

    /** Renders the vertex data associated with this Object.
     * @param   programID   The shader program to buffer the object data to.
     * @param   &viewMatrix Matrix of the player camera's current view. */
    void render(unsigned int programID, glm::mat4 &viewMatrix);

    /** Returns total size of vertex data. */
    unsigned int getVerticesSize() const;
    /** Returns total size of index data. */
    unsigned int getIndicesSize() const;
    /* Returns the scale factor for the object, as a percentage of its original size. */
    float getScaleFactor() const;
    /* Returns the translation of the object from the world origin. */
    glm::vec3 getTranslation();

private:
    /** The actual routine called by constructors etc to set up data and so forth on creation.
     * Thus it should be called ONLY ONCE, and will be done by all constructors.
     * @param   programID   The shader program to buffer the object data to.
     * @param   objfile     The filename of where the data of an OBJ file is stored. 
     * @param   rotate   The amount in the x, y, and z planes that the object will be rotated by.
     * @param   translate The amount in the x, y, and z planes that the object will be translated, relative to the origin of the world.
     * @param   scaleFactor Amount to scale the object by, as a percentage of its original size. Defaults to its initial size if not specified.
     */
    void objectInit(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scaleFactor);

    static const unsigned int mBufSize = 2; // total number of buffers
    unsigned int mBuffer[mBufSize]; // the buffers
    static const unsigned int mVerticesBufPos = 0; // index position of vertices in buffer
    static const unsigned int mIndicesBufPos = 1; // index position of indices in buffer

    unsigned int mVerticesSize; // total number of vertices of the object
    unsigned int mIndicesSize; // total number of indices of the object
    glm::vec3 mCentres; // the centre of the object in the X, Y and Z axes.

    float mScale; // the amount to scale the object's initial size by.
    glm::vec3 mTranslate; // translation from the world origin
    glm::vec3 mRotate; // rotation factors of the object

    unsigned int mVertexVaoHandle; // VAO handle for the object's vertices
};

#endif
