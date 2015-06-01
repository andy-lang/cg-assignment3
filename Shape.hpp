/**********************************************************************
 * Wrapper for a shape object, and its associated vertex & texture data.
 * This is only likely to be called by the Object class, which is just a collection of Shapes.
 * @author	:	Andrew Lang
 * @id		:	a1648205
 * @created :	2015-05-23
 * @project	:	CG assignment 3
**********************************************************************/

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "external_files/soil/src/SOIL.h"
#include "external_files/tiny_obj_loader/tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include <iostream>
#include <sstream>
#include <vector>

class Shape {
public:
	/* Only Shape constructor.
	 * @param	programID	the ID of the program to which the data will be buffered.
	 * @param	shape		The shape data, in the form specified in the tinyobj library.
	 * @param	material	The material data, in the form specified in the tiny obj library.
	 * @param	directory	The directory where shape & material data can be found, relative to the directory in which this executable was called.
	 */
    Shape(int programID, tinyobj::shape_t shape, tinyobj::material_t material, std::string directory);
	/* Basic Shape destructor. */
    ~Shape();

	/* Render the shape and its associated texture data.
	 * @param	programID	The ID of the program to which the data will be buffered.
	 */
    void render(unsigned int programID);

	/* Accessors for data sizes */
    unsigned int getVerticesSize() const;
    unsigned int getIndicesSize() const;
    unsigned int getNormalsSize() const;
    unsigned int getTexCoordsSize() const;

private:
	/* We keep this constructor private since it's of no use to an external user. */
    Shape();

	/* The function that actually initialises the shape data.
	 * @param	programID	the ID of the program to which the data will be buffered.
	 * @param	shape		The shape data, in the form specified in the tinyobj library.
	 * @param	material	The material data, in the form specified in the tiny obj library.
	 * @param	directory	The directory where shape & material data can be found, relative to the directory in which this executable was called.
	 */
    void shapeInit(int programID, tinyobj::shape_t shape, tinyobj::material_t material, std::string directory);

	/* Generates a new texture, and returns the handle for this texture.
	 * @param	filename	The filepath, relative to the directory where the executable was called, where the image file can be found.
	 * @return	A handle to the texture data.
	 */
    unsigned int generateTexture(const char* filename);

    static const unsigned int mBufSize = 4; // size of the buffer
    unsigned int mBuffer[mBufSize]; // the buffer
    static const unsigned int VERTICES_BUF_POS = 0; // position of vertex data in the buffer
    static const unsigned int INDICES_BUF_POS = 1; // position of index data in the buffer
    static const unsigned int NORMALS_BUF_POS = 2; // position of normal data in the buffer
    static const unsigned int TEXCOORDS_BUF_POS = 3; // position of texcoord data in the buffer

	/* surface lighting data */
	float mAmbient[VALS_PER_MTL_SURFACE];
	float mDiffuse[VALS_PER_MTL_SURFACE];
	float mSpecular[VALS_PER_MTL_SURFACE];
	float mEmission[VALS_PER_MTL_SURFACE];
	float mShininess;

	/* Sizes of buffered data */
    unsigned int mVerticesSize;
    unsigned int mIndicesSize;
    unsigned int mNormalsSize;
    unsigned int mTexCoordsSize;

    unsigned int mVertexVaoHandle; // VAO handle for vertices
    unsigned int mTextureHandle; // handle for the texture data
};


#endif
