#include "Object.hpp"

Object::Object() {
    //?? TODO: stub
}

Object::Object(int programID) {
    //?? TODO: stub
}

Object::Object(int programID, const char* objfile) {
    objectInit(programID, objfile, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
}

Object::Object(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale) {
    objectInit(programID, objfile, rotate, translate, scale);
}

Object::~Object() {
    //?? TODO: stub
}

void Object::objectInit(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale) {
    // initialise values
    mVerticesSize = 0;
    mIndicesSize = 0;
    mNormalsSize = 0;
    mTexCoordsSize = 0;
    mCentres = glm::vec3(0.0f, 0.0f, 0.0f);

    setScale(scale);
    setRotation(rotate);
    setTranslation(translate);

    // get directory of passed parameter
    std::string directory = objfile;
    directory = directory.substr(0, directory.find_last_of('/'));
    directory += '/';

    // read in obj file
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string result = LoadObj(shapes, materials, objfile, directory.c_str());

    for (int i = 0; i < shapes.size(); i++) {
        for (int j = 0; j < shapes.at(i).mesh.indices.size(); j++) {
            // adjust indices by some offset so that they point to the correct vertices
            shapes.at(i).mesh.indices.at(j) += mVerticesSize/VALS_PER_VERT;
        }

        for (int j = 0; j < shapes.at(i).mesh.positions.size(); j++) {
            if (j%VALS_PER_VERT == 0) {
                mCentres.x += shapes.at(i).mesh.positions.at(j);
            }
            else if (j%VALS_PER_VERT == 1) {
                mCentres.y += shapes.at(i).mesh.positions.at(j);
            }
            else if (j%VALS_PER_VERT == 2) {
                mCentres.z += shapes.at(i).mesh.positions.at(j);
            }
        }

        mVerticesSize += shapes.at(i).mesh.positions.size();
        mIndicesSize += shapes.at(i).mesh.indices.size();
        mNormalsSize += shapes.at(i).mesh.normals.size();
        mTexCoordsSize += shapes.at(i).mesh.texcoords.size();
    }

    mCentres.x /= (mVerticesSize/VALS_PER_VERT);
    mCentres.y /= (mVerticesSize/VALS_PER_VERT);
    mCentres.z /= (mVerticesSize/VALS_PER_VERT);



    glGenBuffers(mBufSize, mBuffer);

    // generate vertex arrays
    glGenVertexArrays(1, &mVertexVaoHandle);
    glBindVertexArray(mVertexVaoHandle);
    int vertLoc = glGetAttribLocation(programID, "a_vertex");
    int normLoc = glGetAttribLocation(programID, "a_normal");
    int texLoc = glGetAttribLocation(programID, "a_tex_coord");


    // here's where the fun begins. Buffers awaaaay~
    //
    // buffer vertices
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[VERTICES_BUF_POS]);
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer[INDICES_BUF_POS]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesSize*sizeof(unsigned int), 0, GL_STATIC_DRAW);
    for (int i = 0; i < shapes.size(); i++) {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, szCount*sizeof(unsigned int), shapes.at(i).mesh.indices.size()*sizeof(unsigned int), &shapes.at(i).mesh.indices.front());
        szCount += shapes.at(i).mesh.indices.size();
    }
    
    // buffer normals
    szCount = 0;
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[NORMALS_BUF_POS]);
    glBufferData(GL_ARRAY_BUFFER, mNormalsSize*sizeof(float), 0, GL_STATIC_DRAW);
    for (int i = 0; i < shapes.size(); i++) {
        glBufferSubData(GL_ARRAY_BUFFER, szCount*sizeof(float), shapes.at(i).mesh.normals.size()*sizeof(float), &shapes.at(i).mesh.normals.front());
        szCount += shapes.at(i).mesh.normals.size();
    }
    glEnableVertexAttribArray(normLoc);
    glVertexAttribPointer(normLoc, VALS_PER_NORM, GL_FLOAT, GL_FALSE, 0, 0);

    if (mTexCoordsSize > 0) {
        // if there are any texcoords, then we buffer them, and map textures to them.
        // buffer textures
        szCount = 0;
        glBindBuffer(GL_ARRAY_BUFFER, mBuffer[TEXCOORDS_BUF_POS]);
        glBufferData(GL_ARRAY_BUFFER, mTexCoordsSize*sizeof(float), 0, GL_STATIC_DRAW);
        for (int i = 0; i < shapes.size(); i++) {
            glBufferSubData(GL_ARRAY_BUFFER, szCount*sizeof(float), shapes.at(i).mesh.texcoords.size()*sizeof(float), &shapes.at(i).mesh.texcoords.front());
            szCount += shapes.at(i).mesh.texcoords.size();
        }
        glEnableVertexAttribArray(texLoc);
        glVertexAttribPointer(texLoc, VALS_PER_TEXCOORD, GL_FLOAT, GL_FALSE, 0, 0);



        glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // next, bind textures
        glActiveTexture(GL_TEXTURE0);
        mTextureHandle.resize(shapes.size());
        glGenTextures(shapes.size(), &mTextureHandle.front());

        for (int i = 0; i < materials.size(); i++) {
            int x, y, n;
            if (!materials.at(i).diffuse_texname.empty()) {
                unsigned char* img = SOIL_load_image((directory+materials.at(i).diffuse_texname).c_str(), &x, &y, &n, SOIL_LOAD_RGB);
                if (n == 3) {
                    glBindTexture(GL_TEXTURE_2D, mTextureHandle.at(i));
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
                }
                else if (n == 4) {
                    glBindTexture(GL_TEXTURE_2D, mTextureHandle.at(i));
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
                }
                SOIL_free_image_data(img);
            }
            else {
                // no texture file given, so make it a nice default shade of green.
                unsigned char data[4] = {0.0f, 1.0f, 0.0f, 1.0f};
                glBindTexture(GL_TEXTURE_2D, mTextureHandle.at(i));
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
        }
    }
    else {
        // no texture files whatsoever.
        // we combat this by making a default white texture image, and binding it to each of the shapes
        mTextureHandle.resize(shapes.size());
        glGenTextures(shapes.size(), &mTextureHandle.front());
        unsigned char data[4] = {255, 255, 255, 255};
        for (int i = 0; i < shapes.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, mTextureHandle.at(i));
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
    }


    // unbind vertex array
    glBindVertexArray(0);
    // and unbind the buffer too
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // and we're done!
}

void Object::calcModelMatrix() {
    if (mModelMatrixChanged) {
        // create model matrix
        mModelMatrix = glm::mat4();
        //translate to the origin, then by the translate amount
        mModelMatrix = glm::translate(mModelMatrix, glm::vec3(-mCentres.x+mTranslate.x, -mCentres.y+mTranslate.y, -mCentres.z+mTranslate.z));
        // rotate by desired amounts
        mModelMatrix = glm::rotate(mModelMatrix, mRotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
        mModelMatrix = glm::rotate(mModelMatrix, mRotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
        mModelMatrix = glm::rotate(mModelMatrix, mRotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
        // scale
        mModelMatrix = glm::scale(mModelMatrix, glm::vec3(mScale, mScale, mScale));
    }
    mModelMatrixChanged = false; // set flag back to false, so function isn't called again on next render
    // else do nothing

}

void Object::render(unsigned int programID) {
    int modelHandle = glGetUniformLocation(programID, "model_matrix");
    if (modelHandle == -1) {
        std::cerr << "Could not find uniform variable 'model_matrix'" << std::endl;
        exit(1);
    }
    int texMapHandle = glGetUniformLocation(programID, "tex_map");
    if (texMapHandle == -1) {
        std::cerr << "Could not find uniform variable 'tex_map'" << std::endl;
        exit(1);
    }


    glActiveTexture(GL_TEXTURE0);
    for (int i = 0; i < mTextureHandle.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, mTextureHandle.at(i));
    }
    calcModelMatrix();
    glUniformMatrix4fv(modelHandle, 1, false, glm::value_ptr(mModelMatrix));

    glBindVertexArray(mVertexVaoHandle);
    glDrawElements(GL_TRIANGLES, mIndicesSize, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0); // unbind VAO
    glutSwapBuffers();

}

void Object::setRotation(glm::vec3 rotation) {
    mRotate = rotation;
    mModelMatrixChanged = true;
}

void Object::setScale(float scale) {
    mScale = scale;
    mModelMatrixChanged = true;
}

void Object::setTranslation(glm::vec3 translation) {
    mTranslate = translation;
    mModelMatrixChanged = true;
}

unsigned int Object::getVerticesSize() const {
    return mVerticesSize;
}

unsigned int Object::getIndicesSize() const {
    return mIndicesSize;
}

float Object::getScaleFactor() const {
    return mScale;
}

glm::vec3 Object::getTranslation() {
    return mTranslate;
}

glm::vec3 Object::getPosition() {
     return glm::vec3(-mCentres.x+mTranslate.x, -mCentres.y+mTranslate.y, -mCentres.z+mTranslate.z);
}
