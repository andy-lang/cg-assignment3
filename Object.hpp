/**********************************************************************
 * Class representing a particular entity in the world of the program.
 * In reality, all this does is hold a collection of shapes, each of
 * which are individually buffered and rendered.
 * However, it is still best to call this class' render() function, rather than creating Shapes individually.
 *
 * @author 	: Andrew Lang
 * @id 		: a1648205
 * @created 	: 2015-05-07
 * @project 	: CG Assignment 3
**********************************************************************/

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "external_files/soil/src/SOIL.h"
#include "external_files/tiny_obj_loader/tiny_obj_loader.h" // obj file reading

#include <GL/glut.h>

#include "libs/Lib.h"
#include "Shape.hpp"
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
     * All other parameters are set to sensibly default values.
     * @param   programID   The shader program to buffer the object data to.
     * @param   objfile     The filename of where the data of an OBJ file is stored. 
     */
    Object(int programID, const char* objfile);

    /** Advanced Object constructor.
     * Takes in a filename corresponding to an OBJ file, which it reads in and sets up the necessary data.
     * Also contains parameters for more advanced stuff, like scaling, translation, etc.
     * @param   programID   The shader program to buffer the object data to.
     * @param   objfile     The filename of where the data of an OBJ file is stored. 
     * @param   rotations   The amount in the x, y, and z planes that the object will be rotated by.
     * @param   translate The amount in the x, y, and z planes that the object will be translated, relative to the origin of the world.
     * @param   scale Amount to scale the object by, as a percentage of its original size. Defaults to its initial size if not specified.
     */
    Object(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale);

    /* Basic Object destructor. */
    ~Object();

    /** Renders the vertex data associated with this Object.
     * @param   programID   The shader program to buffer the object data to.
     * @param   &viewMatrix Matrix of the player camera's current view. */
    void render(unsigned int programID);

    /* Sets values for rotation, scale and translation, and notifies the model matrix so it can be recalculated. */
    void setRotation(glm::vec3 rotation);
    void setScale(float scale);
    void setTranslation(glm::vec3 translation);

    /** Returns total size of vertex data. */
    unsigned int getVerticesSize() const;
    /** Returns total size of index data. */
    unsigned int getIndicesSize() const;
	/** Returns total size of normal data. */
	unsigned int getNormalsSize() const;
	/** Returns total size of texcoords data. */
	unsigned int getTexCoordsSize() const;

    /* Returns the scale factor for the object, as a percentage of its original size. */
    float getScaleFactor() const;
    /* Returns the translation of the object. */
    glm::vec3 getTranslation();
    /* Returns the rotation of the object. */
    glm::vec3 getRotation();

    /* Returns the world position of the object. */
    glm::vec3 getPosition();

	glm::mat4 getModelMatrix();

protected:
    /* We keep the most basic Object creator private, so that it's not erroneously called. */
    Object();

    /** The actual routine called by constructors etc to set up data, textures, etc on creation.
     * Thus it should be called ONLY ONCE, and will be done by all constructors.
     * @param   programID   The shader program to buffer the object data to.
     * @param   objfile     The filename of where the data of an OBJ file is stored. 
     * @param   rotate   The amount in the x, y, and z planes that the object will be rotated by.
     * @param   translate The amount in the x, y, and z planes that the object will be translated, relative to the origin of the world.
     * @param   scale Amount to scale the object by, as a percentage of its original size. Defaults to its initial size if not specified.
     */
    void objectInit(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale);

    /* Recalculates the object's model matrix, only if new values have been set. */
    void calcModelMatrix();

    unsigned int mVerticesSize; // total number of vertices of the object
    unsigned int mIndicesSize; // total number of indices of the object
    unsigned int mNormalsSize; // total number of normals of the object
    unsigned int mTexCoordsSize; // total number of tex coordinates of the object
	std::vector<Shape> mShapes; // the shapes that make up the object.
    glm::vec3 mCentres; // the centre of the object in the X, Y and Z axes.
	
    glm::vec3 mRotate; // rotation factors of the object
    float mScale; // the amount to scale the object's initial size by.
    glm::vec3 mTranslate; // translation from the world origin

    bool mModelMatrixChanged; // true if any of the values relating to the model matrix have been changed since the last render call.
    glm::mat4 mModelMatrix; // the object's model matrix.
};

#endif
