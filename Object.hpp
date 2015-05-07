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
     * @param   objfile The filename where the data of an OBJ file is stored. 
     * @param   programID   The shader program to buffer the object data to.
     */
    Object(const char* objfile, int programID);

    /* Basic Object destructor. */
    ~Object();

    /** Renders the vertex data associated with this Object. */
    void render(unsigned int programID);

    /** Returns total size of vertex data. */
    unsigned int getVerticesSize() const;
    /** Returns total size of index data. */
    unsigned int getIndicesSize() const;

private:
    static const unsigned int mBufSize = 2;
    unsigned int mBuffer[mBufSize];
    static const unsigned int mVerticesBufPos = 0;
    static const unsigned int mIndicesBufPos = 1;

    unsigned int mVerticesSize;
    unsigned int mIndicesSize;

    float yRot;
    unsigned int mVertexVaoHandle;
};

#endif
