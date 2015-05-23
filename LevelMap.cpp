#include "LevelMap.hpp"

std::vector<Object> generateLevelMap(int programID, std::vector<Object> objects){
	std::vector<Object> obj = objects;

	Object obj1(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f), 0.5f);
    obj.push_back(obj1);

	return obj;
}