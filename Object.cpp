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

		Shape *sh = new Shape(programID, shapes.at(i), materials.at(i), directory);
		mShapes.push_back(sh);
    }

    mCentres.x /= (mVerticesSize/VALS_PER_VERT);
    mCentres.y /= (mVerticesSize/VALS_PER_VERT);
    mCentres.z /= (mVerticesSize/VALS_PER_VERT);
}

/*
int Object::generateTexture(const char* filename) {
	int x, y, n;
	unsigned char* img = SOIL_load_image(filename, &x, &y, &n, SOIL_LOAD_RGB);
	std::cout << "x = " << x << ", y = " << y << " | n = " << n << std::endl;

	unsigned int textureHandle;
	glGenTextures(1, &textureHandle);

	glBindTexture(GL_TEXTURE_2D, textureHandle);

	if (n == 3) {
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	}
	else if (n == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	}
	else {
		// if n is 0 or some other mad number, we have an error on our hands.
		// we draw a white image to represent this.
		std::cerr << "file " << filename << " is not a valid image file. Creating default image as substitute" << std::endl;
		unsigned char def[4] = {0, 0, 0, 255};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, def);
	}
	SOIL_free_image_data(img);

	// while we're into the swing of things, we also set some texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return textureHandle;
}
*/

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
	glUseProgram(programID);
    int modelHandle = glGetUniformLocation(programID, "model_matrix");
    if (modelHandle == -1) {
        std::cerr << "Could not find uniform variable 'model_matrix'" << std::endl;
        exit(1);
    }

    calcModelMatrix();
    glUniformMatrix4fv(modelHandle, 1, false, glm::value_ptr(mModelMatrix));

	for (int i = 0; i < mShapes.size(); i++) {
	    mShapes.at(i)->render(programID);
	}
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

glm::vec3 Object::getRotation() {
    return mRotate;
}

glm::vec3 Object::getPosition() {
     return glm::vec3(-mCentres.x+mTranslate.x, -mCentres.y+mTranslate.y, -mCentres.z+mTranslate.z);
}
