#include "Shape.hpp"

Shape::Shape() {
    //?? TODO: stub
}

Shape::Shape(int programID, tinyobj::shape_t shape, tinyobj::material_t material, std::string directory) {
    shapeInit(programID, shape, material, directory);
}

void Shape::shapeInit(int programID, tinyobj::shape_t shape, tinyobj::material_t material, std::string directory) {
    mVerticesSize = shape.mesh.positions.size();
    mIndicesSize = shape.mesh.indices.size();
    mNormalsSize = shape.mesh.normals.size();
    mTexCoordsSize = shape.mesh.texcoords.size();


    glGenBuffers(mBufSize, mBuffer);

    glGenVertexArrays(1, &mVertexVaoHandle);
    glBindVertexArray(mVertexVaoHandle);

    int vertLoc = glGetAttribLocation(programID, "a_vertex");
    int normLoc = glGetAttribLocation(programID, "a_normal");
    int texLoc = glGetAttribLocation(programID, "a_tex_coord");

    // buffer vertices
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[VERTICES_BUF_POS]);
    glBufferData(GL_ARRAY_BUFFER, mVerticesSize*sizeof(float), &shape.mesh.positions.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertLoc);
    glVertexAttribPointer(vertLoc, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);

    // buffer indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer[INDICES_BUF_POS]);
    glBufferData(GL_ARRAY_BUFFER, mIndicesSize*sizeof(unsigned int), &shape.mesh.indices.front(), GL_STATIC_DRAW);

    // buffer normals
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[NORMALS_BUF_POS]);
    glBufferData(GL_ARRAY_BUFFER, mNormalsSize*sizeof(float), &shape.mesh.normals.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(normLoc);
    glVertexAttribPointer(normLoc, VALS_PER_NORM, GL_FLOAT, GL_FALSE, 0, 0);

    if (mTexCoordsSize > 0) {
        // buffer texcoords
        glBindBuffer(GL_ARRAY_BUFFER, mBuffer[TEXCOORDS_BUF_POS]);
        glBufferData(GL_ARRAY_BUFFER, mTexCoordsSize*sizeof(float),&shape.mesh.texcoords.front(), GL_STATIC_DRAW);

        // bind texture
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &mTextureHandle);
        mTextureHandle = generateTexture((directory+material.diffuse_texname).c_str());
    }
    else {
        // no texture file given, so we create a default
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &mTextureHandle);
        mTextureHandle = generateTexture("");
    }

    // unbind vertex array
    glBindVertexArray(0);
    // unbind the buffer too
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // and we're done!
}

int Shape::generateTexture(const char* filename) {
    //?? TODO: stub
}

void Shape::render(unsigned int programID) {
    //?? TODO: stub
}

unsigned int Shape::getVerticesSize() const {
    return mVerticesSize;
}

unsigned int Shape::getIndicesSize() const {
    return mIndicesSize;
}

unsigned int Shape::getNormalsSize() const {
    return mNormalsSize;
}

unsigned int Shape::getTexCoordsSize() const {
    return mTexCoordsSize;
}
