#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "Shader.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "libs/Lib.h"
#include "LevelMap.hpp"

#include <iostream>
#include <cstdlib>
//#include <string>

std::vector<unsigned int> programIDs;

std::vector<Object> objects;
std::vector<Camera> cameras;
int camIdx;
Player* player;

double FOV = 45.0;
bool lMousePressed;
bool rMousePressed;

void setCamera() {
    glm::mat4 projection;
    projection = glm::infinitePerspective(FOV, double(WINDOW_WIDTH)/double(WINDOW_HEIGHT), 1.0);

	for (int i = 0; i < programIDs.size(); i++) {
		glUseProgram(programIDs.at(i));
		int projHandle = glGetUniformLocation(programIDs.at(i), "projection_matrix");
		if (projHandle == -1) {
			std::cerr << "'projection_matrix' is not an active uniform label." << std::endl;
			exit(1);
		}
		glUniformMatrix4fv(projHandle, 1, false, glm::value_ptr(projection));
	}
}

/* Set up all required objects etc.
 * Returns 0 on success, nonzero otherwise. */
int objectSetup() {
    objects = generateLevelMap(programIDs[0], objects);

	for (int i = 0; i < programIDs.size(); i++) {
		/*
		Object tet(programIDs.at(i), "geom/tetra/tetra.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 5.0f), 1.0f);
		objects.push_back(tet);
		*/

		// test for a whole bunch of objects - good as a basic check for efficiency
		/*
		for (int j = 0; j < 100; j++) {
			Object obj(programIDs.at(i), "geom/cube-simple/cube-simple.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2*float(j), 0.0f, 0.0f), 1.0f);
			objects.push_back(obj); 
		}
		*/
		//objects.push_back(player);

	}
	glUseProgram(programIDs.at(0));

	//Object tet(programIDs.at(0), "geom/tetra/tetra.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, 5.0f), 1.0f);
	//objects.push_back(tet);

	//player = new Player(programIDs.at(0), "geom/cube-tex/cube-tex.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, -5.0f), 1.0f);
	player = new Player(programIDs.at(0), "geom/cube-tex/cube-tex.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.0f, -5.0f), 1.0f);
    camIdx = 1;
    Camera firstPerson = Camera();
    firstPerson.attachToObject(player, glm::vec3(0.0f, 0.0f, 1.0f));
    cameras.push_back(firstPerson);

    Camera thirdPerson = Camera();
    thirdPerson.attachToObject(player, glm::vec3(0.0f, 2.0f, -5.0f));
    cameras.push_back(thirdPerson);

    return 0;
}

/* Sets up all things that will be used frequently by the program - camera, objects, etc.
 * Thus it should be called only once by the application, before any rendering is done. */
int setup() {
    setCamera();
    if (objectSetup() != 0) {
        return 1;
    }
    return 0;
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < programIDs.size(); i++) {
		glUseProgram(programIDs.at(i));
		//glGenerateMipmap(GL_TEXTURE_2D);

		cameras.at(camIdx).render(programIDs.at(i));
		player->render(programIDs.at(i));
		for (int j = 0; j < objects.size(); j++) {
			objects.at(j).render(programIDs.at(i));
		}

	}
    glutSwapBuffers();
    glFlush();
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
        case 'q':
            exit(0);
            break;
        case 'a':
            player->moveLeft();
            glutPostRedisplay();
            break;
        case 'd':
            player->moveRight();
            glutPostRedisplay();
            break;
        case 'w':
            player->moveForward();
            glutPostRedisplay();
            break;
        case 's':
            player->moveBackward();
            glutPostRedisplay();
            break;
        case 'f':
            camIdx = (camIdx+1)%cameras.size();
            if (camIdx == 0) {
                std::cout << "first person" << std::endl;
            }
            else if (camIdx == 1) {
                std::cout << "third person" << std::endl;
            }
            glutPostRedisplay();
            break;

        case 'l':
            int pMode;
            glGetIntegerv(GL_POLYGON_MODE, &pMode);
            if (pMode == GL_FILL) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            glutPostRedisplay();
            break;

    }
}

void specialFunc(int key, int x, int y) {
    /*
    switch (key) {
        case GLUT_KEY_LEFT:
            yRot -= 2.0f;
            break;
        case GLUT_KEY_RIGHT:
            yRot += 2.0f;
            break;
    }
    glutPostRedisplay();
    */
}

void mouseFunc(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                lMousePressed = true;
            }
            else {
                lMousePressed = false;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                rMousePressed = true;
            }
            else {
                rMousePressed = false;
            }
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    // Set up basic window management stuff.
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Computer Graphics, S1 2015 - Assignment 3");

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialise GLEW." << std::endl;
        return -1;
    }

    // load and compile shader files
    unsigned int programID1 = LoadShaders("wireframe.vert", "wireframe.frag");
    if (programID1 == 0) {
        return 1;
    }
	programIDs.push_back(programID1);

	/*
	unsigned int programID2 = LoadShaders("wireframe2.vert", "wireframe2.frag");
	if (programID2 == 0) {
	    return 1;
	}
	programIDs.push_back(programID2);
	*/

    if (setup() != 0) {
        std::cerr << "setup() failed." << std::endl;
        return 1;
    }

    // set background colour
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // enable transparency effects
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // wireframes for now
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // set up GLUT functions with associated application functions
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(render);

    std::cout << "WASD keys to move" << std::endl;
    std::cout << "F to switch camera views" << std::endl;
    std::cout << "L to switch polygon mode" << std::endl;
    glutMainLoop();
    return 0;
}
