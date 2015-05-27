/**********************************************************************
 * Level map generation
 *
 * @author  : Gavin Meredith
 * @id      : a1645739
 * @created     : 2015-05-16
 * @project     : CG Assignment 3
**********************************************************************/

#ifndef MAP_HPP
#define MAP_HPP

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "external_files/soil/src/SOIL.h"
#include "external_files/tiny_obj_loader/tiny_obj_loader.h"

#include <GL/glut.h>

#include "libs/Lib.h"
#include "Object.hpp"
#include <iostream>
#include <vector>

std::vector<Object> generateLevelMap(int programID, std::vector<Object> objects);

#endif
