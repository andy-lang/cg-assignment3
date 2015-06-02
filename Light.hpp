/**********************************************************************
 * Class representing a single light source in the game world.
 *
 * @author 	: Andrew Lang
 * @id 		: a1648205
 * @created 	: 2015-05-30
 * @project 	: CG Assignment 3
**********************************************************************/

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include <GL/glut.h>

#include "libs/Lib.h"
#include <iostream>

class Light {
public:
	/* Basic Light constructor. */
    Light();

	/*
	 * Advanced Light constructor.
	 * Takes in parameters to specify position, and ambient/diffuse/specular colours.
	 *
	 * @param	position	The position of the light in the world space.
	 * @param	ambient		The ambient light values for the light source.
	 * @param	diffuse		The diffuse light values for the light source.
	 * @param	specular	The specular light values for the light source.
	 * @param	brightness	The brightness of the light source. Set to a value of 1.0f by default.
	 */
    Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float brightness = 1.0f);

	/* Light destructor. */
    ~Light();


	/* Getters */
	glm::vec3 getPosition();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	float getBrightness();

	/* Setters */
	void setPosition(glm::vec3 position);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setBrightness(float brightness);

private:
	glm::vec3 mPosition; // position of the light in the world space.
	glm::vec3 mAmbient; // ambient light
	glm::vec3 mDiffuse; // diffuse light
	glm::vec3 mSpecular; // specular light
	float mBrightness;
};


#endif
