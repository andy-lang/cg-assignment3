/**********************************************************************
 * Level map generation
 *
 * @author  : Gavin Meredith
 * @id      : a1645739
 * @created     : 2015-05-16
 * @project     : CG Assignment 3
**********************************************************************/

#include "LevelMap.hpp"

Object create(int programID, const char* file, glm::vec3 rot, glm::vec3 pos, float scale){
    Object obj(programID, file, rot, pos, scale);
    return obj;
}

std::vector<Object> generateLevelMap(int programID, std::vector<Object> objects){
	std::vector<Object> obj = objects;

	//O0
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
	//O1
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.5f));
    //O2
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), 0.5f));
    //O3
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(1.0f, 0.0f, 2.0f), 0.5f));
    //O4
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 3.0f), 0.5f));
    //O5
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 4.0f), 0.5f));
    //O6
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 5.0f), 0.5f));
    //O7
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 6.0f), 0.5f));
    //O8
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 7.0f), 0.5f));
    //O9
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(1.0f, 0.0f, 8.0f), 0.5f));
    //O10
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, 8.0f), 0.5f));
    //O11
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 8.0f), 0.5f));
    //O12
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, 9.0f), 0.5f));
    //O13
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f), 0.5f));
    //O14
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 11.0f), 0.5f));
    //O15
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-2.0f, 0.0f, 11.0f), 0.5f));
    //O16
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-3.0f, 0.0f, 11.0f), 0.5f));
    //O17
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-4.0f, 0.0f, 11.0f), 0.5f));
    //O18
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-5.0f, 0.0f, 10.0f), 0.5f));
    //O19
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-5.0f, 0.0f, 9.0f), 0.5f));
    //O20
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-4.0f, 0.0f, 8.0f), 0.5f));
    //O21
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-5.0f, 0.0f, 8.0f), 0.5f));
    //O22
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-6.0f, 0.0f, 8.0f), 0.5f));
    //O23
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-7.0f, 0.0f, 7.0f), 0.5f));
    //O24
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-7.0f, 0.0f, 6.0f), 0.5f));
    //O25
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-8.0f, 0.0f, 5.0f), 0.5f));
    //O26
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-7.0f, 0.0f, 4.0f), 0.5f));
    //O27
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-7.0f, 0.0f, 3.0f), 0.5f));
    //O28
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-6.0f, 0.0f, 2.0f), 0.5f));
    //O29
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-5.0f, 0.0f, 2.0f), 0.5f));
    //O30
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-4.0f, 0.0f, 2.0f), 0.5f));
    //O31
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-3.0f, 0.0f, 2.0f), 0.5f));
    //O32
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-2.0f, 0.0f, 2.0f), 0.5f));
    //O33
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 2.0f), 0.5f));
    //O34
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 1.0f), 0.5f));
    //O35
    obj.push_back(create(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), 0.5f));
    //floor
    obj.push_back(create(programID, "geom/floor_cube/floor_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-3.0f, -0.5f, 5.0f), 0.5f));
    //ceiling
    obj.push_back(create(programID, "geom/ceiling_cube/ceiling_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-3.0f, 0.5f, 5.0f), 0.5f));

	return obj;
}