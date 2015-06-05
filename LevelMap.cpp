#include "LevelMap.hpp"
#include <math.h>

Object createObj(int programID, const char* file, glm::vec3 rot, glm::vec3 pos, float scale){
    Object obj(programID, file, rot, pos, scale);
    return obj;
}

Light createLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float brightness = 1.0f) {
	Light light(pos, amb, diff, spec, brightness);
	return light;
}

void generateLevelMap(int programID, std::vector<Object> &obj, std::vector<Light> &lights){
	//O0
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
	//O1
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.5f));
    //O2
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), 0.5f));
    //O3
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 2.0f), 0.5f));
    //O4
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 3.0f), 0.5f));
    //O5
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 4.0f), 0.5f));
    //O6
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 5.0f), 0.5f));
    //O7
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 6.0f), 0.5f));
    //O8
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 7.0f), 0.5f));
    //O9
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 8.0f), 0.5f));
    //O10
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 8.0f), 0.5f));
    //O11
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 8.0f), 0.5f));
    //O12
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 9.0f), 0.5f));
    //O13
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f), 0.5f));
    //O14
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 11.0f), 0.5f));
    //O15
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-2.0f, 0.0f, 11.0f), 0.5f));
    //O16
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-3.0f, 0.0f, 11.0f), 0.5f));
    //O17
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-4.0f, 0.0f, 11.0f), 0.5f));
    //O18
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-5.0f, 0.0f, 10.0f), 0.5f));
    //O19
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-5.0f, 0.0f, 9.0f), 0.5f));
    //O20
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-4.0f, 0.0f, 8.0f), 0.5f));
    //O21
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-5.0f, 0.0f, 8.0f), 0.5f));
    //O22
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-6.0f, 0.0f, 8.0f), 0.5f));
    //O23
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-7.0f, 0.0f, 7.0f), 0.5f));
    //O24
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-7.0f, 0.0f, 6.0f), 0.5f));
    //O25
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-8.0f, 0.0f, 5.0f), 0.5f));
    //O26
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-7.0f, 0.0f, 4.0f), 0.5f));
    //O27
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-7.0f, 0.0f, 3.0f), 0.5f));
    //O28
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-6.0f, 0.0f, 2.0f), 0.5f));
    //O29
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-5.0f, 0.0f, 2.0f), 0.5f));
    //O30
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-4.0f, 0.0f, 2.0f), 0.5f));
    //O31
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-3.0f, 0.0f, 2.0f), 0.5f));
    //O32
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-2.0f, 0.0f, 2.0f), 0.5f));
    //O33
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 2.0f), 0.5f));
    //O34
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 1.0f), 0.5f));
    //O35
    obj.push_back(createObj(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), 0.5f));
    //floor
    obj.push_back(createObj(programID, "geom/floor_cube/floor_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-3.0f, -0.5f, 5.0f), 0.5f));
    //ceiling
    obj.push_back(createObj(programID, "geom/ceiling_cube/ceiling_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-3.0f, 0.5f, 5.0f), 0.5f));


    //torches
    //t1
    obj.push_back(createObj(programID, "geom/torch/torch.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-3.5f, 0.3f, 2.9f), 0.25f));
    //t2
    obj.push_back(createObj(programID, "geom/torch/torch.obj", glm::vec3(0.0f, (270.0*M_PI/180.0), 0.0f), glm::vec3(1.54f, 0.3f, 5.5f), 0.25f));
    //t3
    obj.push_back(createObj(programID, "geom/torch/torch.obj", glm::vec3(0.0f, (180.0*M_PI/180.0), 0.0f), glm::vec3(0.0f, 0.3f, 7.95f), 0.25f));
    //t4
    obj.push_back(createObj(programID, "geom/torch/torch.obj", glm::vec3(0.0f, (180.0*M_PI/180.0), 0.0f), glm::vec3(-5.0f, 0.3f, 7.95f), 0.25f));
    //t5
    obj.push_back(createObj(programID, "geom/torch/torch.obj", glm::vec3(0.0f, (180.0*M_PI/180.0), 0.0f), glm::vec3(-2.5f, 0.3f, 10.95f), 0.25f));

	//light sources
	glm::vec3 orange = glm::vec3(0.9f, 0.3f, 0.0f);
	//l1 - corresponds to t1
	lights.push_back(createLight(glm::vec3(-3.5f, 0.3f, 2.9f), glm::vec3(0.0f, 0.0f, 0.0f), orange, glm::vec3(0.8f, 0.2f, 0.0f), 3.0f));
	//l2 - corresponds to t2
	lights.push_back(createLight(glm::vec3(1.44f, 0.3f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), orange, glm::vec3(0.8f, 0.2f, 0.0f), 3.0f));
	//l3 - corresponds to t3
	lights.push_back(createLight(glm::vec3(0.0f, 0.3f, 7.4f), glm::vec3(0.0f, 0.0f, 0.0f), orange, glm::vec3(0.8f, 0.2f, 0.0f), 3.0f));
	//l4 - corresponds to t4
	lights.push_back(createLight(glm::vec3(-5.0f, 0.3f, 6.95f), glm::vec3(0.0f, 0.0f, 0.0f), orange, glm::vec3(0.8f, 0.2f, 0.0f), 3.0f));
	//l5 - corresponds to t5
	lights.push_back(createLight(glm::vec3(-2.5f, 0.3f, 9.95f), glm::vec3(0.0f, 0.0f, 0.0f), orange, glm::vec3(0.8f, 0.2f, 0.0f), 3.0f));

	// l6. Ambient light source in the middle of the map.
	lights.push_back(createLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.0f), glm::vec3(0.0f), 1.0f)); 
}
