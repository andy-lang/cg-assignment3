#ifndef MAP_HPP
#define MAP_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include "Object.hpp"
#include "Wall.hpp"
#include <iostream>

int generateLevelMap(int programID);
float coordToPos(int coord);

#endif