#ifndef WALL_H
#define WALL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include "Object.hpp"
#include <iostream>

class Wall : public Object{
public:
	Wall(int programID);
	Wall(int programID, const char* objfile);
	Wall(int programID, const char* objfile, glm::vec3 rotate, glm::vec3 translate, float scale);
	~Wall();
private:

};

#endif