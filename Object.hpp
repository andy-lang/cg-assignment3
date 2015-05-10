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
     * @param   programID   The shader program to buffer the object data to.
     * @param   objfile     The filename of where the data of an OBJ file is stored. 
     * @param   scaleFactor Amount to scale the object by, as a percentage of its original size. Defaults to its initial size if not specified.
     */
    Object(int programID, const char* objfile, float scaleFactor = 1.0f);

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

    //double m

private:
    static const unsigned int mBufSize = 2; // total number of buffers
    unsigned int mBuffer[mBufSize]; // the buffers
    static const unsigned int mVerticesBufPos = 0; // index position of vertices in buffer
    static const unsigned int mIndicesBufPos = 1; // index position of indices in buffer

    unsigned int mVerticesSize; // total number of vertices of the object
    unsigned int mIndicesSize; // total number of indices of the object

    float mScale; // the amount to scale the object's initial size by.
    glm::mat3 mTrans; // translation from the world origin
    float yRot; // y rotation factor of the object
    unsigned int mVertexVaoHandle; // VAO handle for the object's vertices
};

#endif
