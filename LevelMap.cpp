#include "LevelMap.hpp"

std::vector<Object> generateLevelMap(int programID, std::vector<Object> objects){
	std::vector<Object> obj = objects;

	//O0
	Object obj0(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 0.5f);
    obj.push_back(obj0);
	//O1
	Object obj1(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.5f);
    obj.push_back(obj1);
    //O2
    Object obj2(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), 0.5f);
    obj.push_back(obj2);
    //O3
    Object obj3(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(1.0f, 0.0f, 2.0f), 0.5f);
    obj.push_back(obj3);
    //O4
    Object obj4(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 3.0f), 0.5f);
    obj.push_back(obj4);
    //O5
    Object obj5(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 4.0f), 0.5f);
    obj.push_back(obj5);
    //O6
    Object obj6(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 5.0f), 0.5f);
    obj.push_back(obj6);
    //O7
    Object obj7(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 6.0f), 0.5f);
    obj.push_back(obj7);
    //O8
    Object obj8(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 7.0f), 0.5f);
    obj.push_back(obj8);
    //O9
    Object obj9(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(1.0f, 0.0f, 8.0f), 0.5f);
    obj.push_back(obj9);
    //O10
    Object obj10(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, 8.0f), 0.5f);
    obj.push_back(obj10);
    //O11
    Object obj11(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 8.0f), 0.5f);
    obj.push_back(obj11);
    //O12
    Object obj12(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, 9.0f), 0.5f);
    obj.push_back(obj12);
    //O13
    Object obj13(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f), 0.5f);
    obj.push_back(obj13);
    //O14
    Object obj14(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 11.0f), 0.5f);
    obj.push_back(obj14);
    //O15
    Object obj15(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-2.0f, 0.0f, 11.0f), 0.5f);
    obj.push_back(obj15);
    //O16
    Object obj16(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-3.0f, 0.0f, 11.0f), 0.5f);
    obj.push_back(obj16);
    //O17
    Object obj17(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-4.0f, 0.0f, 11.0f), 0.5f);
    obj.push_back(obj17);
    //O18
    Object obj18(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-5.0f, 0.0f, 10.0f), 0.5f);
    obj.push_back(obj18);
    //O19
    Object obj19(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-5.0f, 0.0f, 9.0f), 0.5f);
    obj.push_back(obj19);
    //O20
    Object obj20(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-4.0f, 0.0f, 8.0f), 0.5f);
    obj.push_back(obj20);
    //O21
    Object obj21(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-5.0f, 0.0f, 8.0f), 0.5f);
    obj.push_back(obj21);
    //O22
    Object obj22(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-6.0f, 0.0f, 8.0f), 0.5f);
    obj.push_back(obj22);
    //O23
    Object obj23(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-7.0f, 0.0f, 7.0f), 0.5f);
    obj.push_back(obj23);
    //O24
    Object obj24(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-7.0f, 0.0f, 6.0f), 0.5f);
    obj.push_back(obj24);
    //O25
    Object obj25(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-8.0f, 0.0f, 5.0f), 0.5f);
    obj.push_back(obj25);
    //O26
    Object obj26(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-7.0f, 0.0f, 4.0f), 0.5f);
    obj.push_back(obj26);
    //O27
    Object obj27(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-7.0f, 0.0f, 3.0f), 0.5f);
    obj.push_back(obj27);
    //O28
    Object obj28(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-6.0f, 0.0f, 2.0f), 0.5f);
    obj.push_back(obj28);
    //O29
    Object obj29(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-5.0f, 0.0f, 2.0f), 0.5f);
    obj.push_back(obj29);
    //O30
    Object obj30(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-4.0f, 0.0f, 2.0f), 0.5f);
    obj.push_back(obj30);
    //O31
    Object obj31(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-3.0f, 0.0f, 2.0f), 0.5f);
    obj.push_back(obj31);
    //O32
    Object obj32(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-2.0f, 0.0f, 2.0f), 0.5f);
    obj.push_back(obj32);
    //O33
    Object obj33(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 2.0f), 0.5f);
    obj.push_back(obj33);
    //O34
    Object obj34(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 1.0f), 0.5f);
    obj.push_back(obj34);
    //O35
    Object obj35(programID, "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), 0.5f);
    obj.push_back(obj35);

    //floor
    Object objf(programID, "geom/floor_cube/floor_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-3.0f, -0.5f, 5.0f), 0.5f);
    obj.push_back(objf);

    //ceiling
    Object objc(programID, "geom/ceiling_cube/ceiling_cube.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(-3.0f, 0.5f, 5.0f), 0.5f);
    obj.push_back(objc);

	return obj;
}