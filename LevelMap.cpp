#include "LevelMap.hpp"

std::vector<Object> generateLevelMap(int programID, std::vector<Object> objects){
	std::vector<Object> obj = objects;

	Object obj1(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f), 10.0f);
    obj.push_back(obj1);

    //Object obj2(programID, "geom/cube-tex/cube-tex.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
    //obj.push_back(obj2);

	return obj;
}