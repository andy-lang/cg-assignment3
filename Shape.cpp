#include "Shape.hpp"

Shape::Shape() {
    //?? TODO: stub
}

Shape::Shape(int programID, tinyobj::shape_t shape, tinyobj::material_t material, std::string directory) {
    shapeInit(programID, shape, material, directory);
}

Shape::~Shape() {
	//?? TODO: stub
}

void Shape::shapeInit(int programID, tinyobj::shape_t shape, tinyobj::material_t material, std::string directory) {
	glUseProgram(programID);
	std::cout << "entered shapeinit" << std::endl;
    mVerticesSize = shape.mesh.positions.size();
    mIndicesSize = shape.mesh.indices.size();
    mNormalsSize = shape.mesh.normals.size();
    mTexCoordsSize = shape.mesh.texcoords.size();

	std::cout << "mVerticesSize = " << mVerticesSize << std::endl;
	std::cout << "mIndicesSize = " << mIndicesSize << std::endl;
	std::cout << "mNormalsSize = " << mNormalsSize << std::endl;
	std::cout << "mTexCoordsSize = " << mTexCoordsSize << std::endl << std::endl;

	for (int i = 0; i < mTexCoordsSize; i+= VALS_PER_TEXCOORD) {
	    /* code */
	}

    glGenBuffers(mBufSize, mBuffer);

    glGenVertexArrays(1, &mVertexVaoHandle);
    glBindVertexArray(mVertexVaoHandle);

    int vertLoc = glGetAttribLocation(programID, "a_vertex");
    //int normLoc = glGetAttribLocation(programID, "a_normal");
    int texLoc = glGetAttribLocation(programID, "a_tex_coord");

    // buffer vertices
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[VERTICES_BUF_POS]);
    glBufferData(GL_ARRAY_BUFFER, mVerticesSize*sizeof(float), &shape.mesh.positions.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertLoc);
    glVertexAttribPointer(vertLoc, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);

    // buffer indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer[INDICES_BUF_POS]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesSize*sizeof(unsigned int), &shape.mesh.indices.front(), GL_STATIC_DRAW);

    // buffer normals
	/*
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer[NORMALS_BUF_POS]);
    glBufferData(GL_ARRAY_BUFFER, mNormalsSize*sizeof(float), &shape.mesh.normals.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(normLoc);
    glVertexAttribPointer(normLoc, VALS_PER_NORM, GL_FLOAT, GL_FALSE, 0, 0);
	*/

    if (mTexCoordsSize > 0) {
        // buffer texcoords
        glBindBuffer(GL_ARRAY_BUFFER, mBuffer[TEXCOORDS_BUF_POS]);
        glBufferData(GL_ARRAY_BUFFER, mTexCoordsSize*sizeof(float),&shape.mesh.texcoords.front(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(texLoc);
		glVertexAttribPointer(texLoc, VALS_PER_TEXCOORD, GL_FLOAT, GL_FALSE, 0, 0);

        // bind texture
        glActiveTexture(GL_TEXTURE0);
        mTextureHandle = generateTexture((directory+material.diffuse_texname).c_str());
    }
    else {
        // no texture file given, so we create a default
        //glGenTextures(1, &mTextureHandle);
        glActiveTexture(GL_TEXTURE0);
        mTextureHandle = generateTexture("");
    }

    // unbind vertex array
    glBindVertexArray(0);
    // unbind the buffer too
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // and we're done!
}

unsigned int Shape::generateTexture(const char* filename) {
	int x, y, n;

	glActiveTexture(GL_TEXTURE0);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/*
	//unsigned int texhandle = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	//mTextureHandle = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	std::cout << "mTextureHandle = " << mTextureHandle << std::endl;
	if (mTextureHandle == 0) {
		// create default image as substitute
		std::cerr << "file " << filename << " is not a valid image file. Creating default image as substitute." << std::endl;
		unsigned char def[4] = {0, 255, 0, 255};
		glBindTexture(GL_TEXTURE_2D, mTextureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, def);
	}
	*/

	unsigned char *img = SOIL_load_image(filename, &x, &y, &n, SOIL_LOAD_AUTO);
	std::cout << "x = " << x << ", y = " << y << " | n = " << n << std::endl;

	unsigned int texHandle;
	glGenTextures(1, &texHandle);

	glBindTexture(GL_TEXTURE_2D, texHandle);

	if (n == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		checkGLError();
	}
	else {
		std::cerr << "file " << filename << " is not a valid image file. Creating default image file as substitute." << std::endl;
		unsigned char def[3] = {0, 255, 0};
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, def);
	}
	SOIL_free_image_data(img);

	// Linear interpolation filter gives a smoothed out appearance the square pixels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Clamp to edge can help to remove visible seams when lookups are at the edge of the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texHandle;
	//std::cout << "x = " << x << ", y = " << y << " | n = " << n << std::endl << std::endl;
	/*
	if (n == 3) {
		glBindTexture(GL_TEXTURE_2D, texhandle);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	}
	else if (n == 4) {
		glBindTexture(GL_TEXTURE_2D, mTextureHandle);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	}
	*/
	/*
	else {
		std::cerr << "file " << filename << " is not a valid image file. Creating default image as substitute." << std::endl;
		unsigned char def[4] = {255, 255, 255, 255};
		glBindTexture(GL_TEXTURE_2D, texhandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, def);
	}
	*/

	//glBindTexture(GL_TEXTURE_2D, mTextureHandle);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


	//SOIL_free_image_data(img);
}

void Shape::render(unsigned int programID) {
	glUseProgram(programID);

	int texMapHandle = glGetUniformLocation(programID, "tex_map");
	if (texMapHandle == -1) {
	    std::cerr << "Could not find uniform variable 'tex_map'" << std::endl;
		exit(1);
	}

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texMapHandle, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindVertexArray(mVertexVaoHandle);

    glBindTexture(GL_TEXTURE_2D, mTextureHandle);
	glDrawElements(GL_TRIANGLES, mIndicesSize, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0); // unbind VAO
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
