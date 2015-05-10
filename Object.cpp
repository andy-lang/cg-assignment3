#include "Object.hpp"

Object::Object(int programID) {
    /*
    //?? TODO: anything else?

    glGenVertexArrays(1, &mVertexVaoHandle);
    glBindVertexArray(mVertexVaoHandle);

    mVerticesSize = 0;
    mIndicesSize = 0;

    glGenBuffers(mBufSize, mBuffer);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    */
}

Object::Object(const char* objfile, int programID) : mVerticesSize(0), mIndicesSize(0), yRot(20.0f) {
    // get directory of passed parameter
    std::string directory = objfile;
    directory = directory.substr(0, directory.find_last_of('/'));

    // read in obj file
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string result = LoadObj(shapes, materials, objfile, directory.c_str());

    for (int i = 0; i < shapes.size(); i++) {
        for (int j = 0; j < shapes.at(i).mesh.indices.size(); j++) {
            // adjust indices by some offset so that they point to the correct vertices
            shapes.at(i).mesh.indices.at(j) += mVerticesSize/VALS_PER_VERT;
        }

        mVerticesSize += shapes.at(i).mesh.positions.size();
        mIndicesSize += shapes.at(i).mesh.indices.size();
    }

    glGenBuffers(mBufSize, mBuffer);

    // generate vertex arrays
    glGenVertexArrays(1, &mVertexVaoHandle);
    glBindVertexArray(mVertexVaoHandle);
    int vertLoc = glGetAttribLocation(programID, "a_vertex");



    // here's where the fun begins. Buffers awaaaay~
    //
    // buffer vertices
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[mVerticesBufPos]);
    glBufferData(GL_ARRAY_BUFFER, mVerticesSize*sizeof(float), 0, GL_STATIC_DRAW);

    unsigned int szCount = 0;
    for (int i = 0; i < shapes.size(); i++) {
        glBufferSubData(GL_ARRAY_BUFFER, szCount*sizeof(float), shapes.at(i).mesh.positions.size()*sizeof(float), &shapes.at(i).mesh.positions.front()); 
        szCount += shapes.at(i).mesh.positions.size();
    }
    glEnableVertexAttribArray(vertLoc);
    glVertexAttribPointer(vertLoc, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);


    // buffer indices
    szCount = 0;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer[mIndicesBufPos]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesSize*sizeof(unsigned int), 0, GL_STATIC_DRAW);
    for (int i = 0; i < shapes.size(); i++) {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, szCount*sizeof(unsigned int), shapes.at(i).mesh.indices.size()*sizeof(unsigned int), &shapes.at(i).mesh.indices.front());
        szCount += shapes.at(i).mesh.indices.size();
    }

    // unbind vertex array
    glBindVertexArray(0);
    // and unbind the buffer too
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // and we're done!
}

Object::~Object() {
    //?? TODO: stub
}

void Object::render(unsigned int programID, glm::mat4 &viewMatrix) {
    int modelHandle = glGetUniformLocation(programID, "model_matrix");
    int viewHandle = glGetUniformLocation(programID, "view_matrix");
    if (modelHandle == -1) {
        std::cerr << "Could not find uniform variable 'model_matrix'" << std::endl;
        exit(1);
    }
    if (viewHandle == -1) {
        std::cerr << "Could not find uniform variable 'view_matrix'" << std::endl;
        exit(1);
    }

    glm::mat4 modelMatrix;
    modelMatrix = glm::rotate(modelMatrix, yRot, glm::vec3(0.0f, 1.0f, 0.0f));
    //modelMatrix = glm::rotate(modelMatrix, yRot, glm::vec3(1.0f, 0.0f, 0.0f));


    glBindVertexArray(mVertexVaoHandle);
    glUniformMatrix4fv(modelHandle, 1, false, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewHandle, 1, false, glm::value_ptr(viewMatrix));

    glDrawElements(GL_TRIANGLES, mIndicesSize, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0); // unbind VAO
    glutSwapBuffers();

}

unsigned int Object::getVerticesSize() const {
    return mVerticesSize;
}

unsigned int Object::getIndicesSize() const {
    return mIndicesSize;
}
