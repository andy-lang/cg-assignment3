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
	mVerticesSize = shape.mesh.positions.size();
	mIndicesSize = shape.mesh.indices.size();
	mNormalsSize = shape.mesh.normals.size();
	mTexCoordsSize = shape.mesh.texcoords.size();

	// generate the buffer, with appropriate size
	glGenBuffers(mBufSize, mBuffer);

	// generate vertex array for the vertex data
	glGenVertexArrays(1, &mVertexVaoHandle);
	glBindVertexArray(mVertexVaoHandle);

	// get attribute locations
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicesSize*sizeof(unsigned int), &shape.mesh.indices.front(), GL_STATIC_DRAW);

	// buffer normals
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer[NORMALS_BUF_POS]);
	glBufferData(GL_ARRAY_BUFFER, mNormalsSize*sizeof(float), &shape.mesh.normals.front(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(normLoc);
	glVertexAttribPointer(normLoc, VALS_PER_NORM, GL_FLOAT, GL_FALSE, 0, 0);

	if (mTexCoordsSize > 0) {
		// buffer texcoords
		glBindBuffer(GL_ARRAY_BUFFER, mBuffer[TEXCOORDS_BUF_POS]);
		glBufferData(GL_ARRAY_BUFFER, mTexCoordsSize*sizeof(float),&shape.mesh.texcoords.front(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(texLoc);
		glVertexAttribPointer(texLoc, VALS_PER_TEXCOORD, GL_FLOAT, GL_FALSE, 0, 0);

		// bind texture
		glActiveTexture(GL_TEXTURE0);
		mTextureHandle = generateTexture((directory+material.diffuse_texname).c_str(), 0);
		//TODO: Add bumpmap gen code
		mBumpmapTextureHandle = generateTexture((directory+material.normal_texname), 1);
	}
	else {
		// no texture file given, so we create a default
		glActiveTexture(GL_TEXTURE0);
		mTextureHandle = generateTexture("");
		mBumpmapTextureHandle = generateTexture("");
	}

	// unbind vertex array
	glBindVertexArray(0);
	// unbind the buffer too
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// and we're done!
}

unsigned int Shape::generateTexture(const char* filename, const unsigned int texCount) {
	int x, y, n;

	switch (texCount)
	{
		case 0:	glActiveTexture(GL_TEXTURE0); break;
		case 1: glActiveTexture(GL_TEXTURE1); break;
	}

	unsigned char *img = SOIL_load_image(filename, &x, &y, &n, SOIL_LOAD_AUTO);

	unsigned int texHandle;
	glGenTextures(1, &texHandle);

	glBindTexture(GL_TEXTURE_2D, texHandle);

	if (n == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	}
	else {
		std::cerr << "file '" << filename << "' is not a valid image file. Creating default image file as substitute." << std::endl;
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
}

void Shape::render(unsigned int programID) {
	glUseProgram(programID);

	int texMapHandle = glGetUniformLocation(programID, "tex_map");
	int texNormHandle = glGetUniformLocation(programID, "tex_norm");
	if (texMapHandle == -1 || texNormHandle == -1) {
		std::cerr << "Could not find uniform variable 'tex_map' or 'tex_norm'" << std::endl;
		exit(1);
	}

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texMapHandle, 0);
	glUniform1i(texNormHandle, 1);

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
