//?? TODO: documentation, commenting

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "external_files/soil/src/SOIL.h"
#include "tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include <iostream>
#include <sstream>
#include <vector>

class Shape {
public:
    Shape(int programID, tinyobj::shape_t shape, tinyobj::material_t material, std::string directory);
    ~Shape();

    void render(unsigned int programID);

    unsigned int getVerticesSize() const;
    unsigned int getIndicesSize() const;
    unsigned int getNormalsSize() const;
    unsigned int getTexCoordsSize() const;

private:
    Shape();

    void shapeInit(int programID, tinyobj::shape_t shape, tinyobj::material_t material, std::string directory);

    int generateTexture(const char* filename);

    static const unsigned int mBufSize = 4;
    unsigned int mBuffer[mBufSize];
    static const unsigned int VERTICES_BUF_POS = 0;
    static const unsigned int INDICES_BUF_POS = 1;
    static const unsigned int NORMALS_BUF_POS = 2;
    static const unsigned int TEXCOORDS_BUF_POS = 3;

    unsigned int mVerticesSize;
    unsigned int mIndicesSize;
    unsigned int mNormalsSize;
    unsigned int mTexCoordsSize;

    unsigned int mVertexVaoHandle;
    unsigned int mTextureHandle;


};


#endif
