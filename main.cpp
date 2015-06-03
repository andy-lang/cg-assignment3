#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include "external_files/glm/glm/glm.hpp"
#include "external_files/glm/glm/gtc/matrix_transform.hpp"
#include "external_files/glm/glm/gtc/type_ptr.hpp"

#include "Shader.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "libs/Lib.h"
#include "LevelMap.hpp"

#include <iostream>
#include <cstdlib>
#include <math.h>
//#include <string>

std::vector<unsigned int> programIDs;

// main section of objects
std::vector<Object> mainObjects;
std::vector<Light> lights; // vector of light sources
std::vector<Camera> cameras;

// objects relating to lava. Should just be the one item, but could add more if you like
std::vector<Object> lavaObjects;
Light lavaLight;

unsigned int lavaLightInitBrightness = 4.5;

int camIdx;
Player* player;

double FOV = 45.0;
bool lMousePressed;
bool rMousePressed;

// timer variables
int currTime;
int prevTime;
int elapsed;

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

void reshapeWindow(int x, int y) {
    WINDOW_WIDTH = x;
    WINDOW_HEIGHT = y;
    glViewport(0,0,x,y);
    setCamera();
}

/* Set up all required mainObjects etc.
 * Returns 0 on success, nonzero otherwise. */
int mainObjectsetup() {
    generateLevelMap(programIDs[0], mainObjects, lights);

    //Add high poly model
    Object statue(programIDs[0], "geom/statue/statue.obj", glm::vec3(0.0f, M_PI/2.0, 0.0f), glm::vec3(-7.0f, 0.0f, 4.9f), 0.7f);
    mainObjects.push_back(statue);

    Object lava(programIDs[0], "geom/wall_cube/wall_cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-7.0f, -0.8f, 5.0f), 0.5f);
    lavaObjects.push_back(lava);

	lavaLight = Light(glm::vec3(-7.5f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.3f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), lavaLightInitBrightness);
	//lights.push_back(lav1);

	/*
	Light lav2(glm::vec3(-7.0f, 0.5f, 5.0f), glm::vec3(0.4f, 0.1f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), 0.1f);
	lights.push_back(lav2);
	*/

	for (int i = 0; i < programIDs.size(); i++) {
		/*
		Object tet(programIDs.at(i), "geom/tetra/tetra.obj", glm::vec3(0.0f, 0.f, 0.0f), glm::vec3(2.0f, 0.0f, 5.0f), 1.0f);
		mainObjects.push_back(tet);
		*/

		// test for a whole bunch of mainObjects - good as a basic check for efficiency
		/*
		for (int j = 0; j < 100; j++) {
			Object obj(programIDs.at(i), "geom/cube-simple/cube-simple.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2*float(j), 0.0f, 0.0f), 1.0f);
			mainObjects.push_back(obj); 
		}
		*/
		//mainObjects.push_back(player);

	}
	glUseProgram(programIDs.at(0));

	player = new Player(programIDs.at(0), "geom/cube-tex/cube-tex.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.25f);
    camIdx = 0;
    Camera firstPerson = Camera();
    firstPerson.attachToObject(player);
    cameras.push_back(firstPerson);

    Camera thirdPerson = Camera();
    thirdPerson.attachToObject(player, glm::vec3(0.0f, 2.0f, -5.0f));
    cameras.push_back(thirdPerson);

    return 0;
}

/* Sets up all things that will be used frequently by the program - camera, mainObjects, etc.
 * Thus it should be called only once by the application, before any rendering is done. */
int setup() {
    setCamera();
    if (mainObjectsetup() != 0) {
        return 1;
    }
    return 0;
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// compile light positions & values into a single vector to be sent to the shader program
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> ambients;
	std::vector<glm::vec3> diffuses;
	std::vector<glm::vec3> speculars;
	std::vector<float> brightnesses;

	lavaLight.setBrightness(lavaLightInitBrightness + 2*sin(currTime/150));
	lights.push_back(lavaLight);
	for (int i = 0; i < lights.size(); i++) {
		positions.push_back(lights.at(i).getPosition());
		ambients.push_back(lights.at(i).getAmbient());
		diffuses.push_back(lights.at(i).getDiffuse());
		speculars.push_back(lights.at(i).getSpecular());
		brightnesses.push_back(lights.at(i).getBrightness());
	}

	for (int i = 0; i < programIDs.size(); i++) {
		glUseProgram(programIDs.at(i));
		//glGenerateMipmap(GL_TEXTURE_2D);

		int normMtxHandle = glGetUniformLocation(programIDs.at(i), "normal_matrix");
		if (normMtxHandle == -1) {
		    std::cerr << "Could not find uniform variable 'normal_matrix'" << std::endl;
			exit(1);
		}
		
		int posHandle = glGetUniformLocation(programIDs.at(i), "lightPositions");
		int ambientHandle = glGetUniformLocation(programIDs.at(i), "lightAmbients");
		int diffuseHandle = glGetUniformLocation(programIDs.at(i), "lightDiffuses");
		int specularHandle = glGetUniformLocation(programIDs.at(i), "lightSpeculars");
		int brightnessHandle = glGetUniformLocation(programIDs.at(i), "lightBrightnesses");

		if ((posHandle == -1) || (ambientHandle == -1) || (diffuseHandle == -1) || (specularHandle == -1) || (brightnessHandle == -1)) {
			std::cerr << "Could not find light uniform variables." << std::endl;
			exit(1);
		}
		glUniform3fv(posHandle, lights.size(), glm::value_ptr(positions.front()));
		glUniform3fv(ambientHandle, lights.size(), glm::value_ptr(ambients.front()));
		glUniform3fv(diffuseHandle, lights.size(), glm::value_ptr(diffuses.front()));
		glUniform3fv(specularHandle, lights.size(), glm::value_ptr(speculars.front()));
		glUniform1fv(brightnessHandle, lights.size(), &brightnesses.front());

		int textureCodeHandle = glGetUniformLocation(programIDs.at(i), "texture_code");
		int timerHandle = glGetUniformLocation(programIDs.at(i), "program_time");
		if ((textureCodeHandle == -1) || (timerHandle == -1)) {
		    std::cerr << "Could not find uniform procedural texture variables" << std::endl;
			std::cerr << "textureCodeHandle = " << textureCodeHandle << std::endl;
			std::cerr << "timerHandle = " << timerHandle << std::endl;
			exit(1);
		}
		glUniform1i(textureCodeHandle, 0);

		cameras.at(camIdx).render(programIDs.at(i));
		glm::mat4 viewMtx = cameras.at(camIdx).getViewMatrix();

        bool collisionDetected = false;
        glm::vec3 objTranslation;
        glm::vec3 playerTranslation;

		for (int j = 0; j < mainObjects.size(); j++) {
			glm::mat3 normMtx = glm::transpose(glm::inverse(glm::mat3(mainObjects.at(j).getModelMatrix() * viewMtx))); 
			glUniformMatrix3fv(normMtxHandle, 1, false, glm::value_ptr(normMtx));
			mainObjects.at(j).render(programIDs.at(i));

            /***** Main Collision dection alg *****/
            if(j < 36){
                objTranslation = mainObjects.at(j).getTranslation();
                playerTranslation = player->getTranslation();

                float xDiff = std::abs(playerTranslation.x - objTranslation.x);
                float zDiff = std::abs(playerTranslation.z - objTranslation.z);

                float absDist = std::sqrt(std::pow(xDiff, 2.0) + std::pow(zDiff, 2.0));
                float angle = std::atan2(zDiff, xDiff);
                float internalObjDist;
                float internalPlayerDist;

                //Right or Left quad
                if(std::abs(angle) <= M_PI/4.0){
                    internalObjDist = std::abs((0.5)/(std::cos(angle)));
                    internalPlayerDist = std::abs(std::sqrt(pow(0.3, 2) +  pow(0.3, 2)));
                }
                //Top or Bottom quad
                else{
                    angle = M_PI/2.0 - angle;
                    internalObjDist = std::abs((0.5)/(std::cos(angle)));
                    internalPlayerDist = std::abs(std::sqrt(pow(0.3, 2) +  pow(0.3, 2)));
                }

                if((absDist - internalObjDist - internalPlayerDist) < 0){
                    collisionDetected = true;
                }
            }
        }

		// render lava floor
		glUniform1i(textureCodeHandle, 1);
		glUniform1i(timerHandle, currTime);
		for (int j = 0; j < lavaObjects.size(); j++) {
			glm::mat3 normMtx = glm::transpose(glm::inverse(glm::mat3(lavaObjects.at(j).getModelMatrix() * viewMtx))); 
			glUniformMatrix3fv(normMtxHandle, 1, false, glm::value_ptr(normMtx));
			lavaObjects.at(j).render(programIDs.at(i));
		}

        if(collisionDetected){
            player->setPrevPos();
        }

		glUniform1i(textureCodeHandle, 0); // need to render player with regular texturing, not procedural
        player->render(programIDs.at(i));        
	}
	lights.erase(lights.end()); // remove the lava light source from the lights again

    glutSwapBuffers();
    glFlush();
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Esc
            exit(1);
            break;
        case 'a':
            player->strafeLeft();
            glutPostRedisplay();
            break;
        case 'd':
            player->strafeRight();
            glutPostRedisplay();
            break;
        case 'q':
            player->rotLeft();
            glutPostRedisplay();
            break;
        case 'e':
            player->rotRight();
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

void timer(int value) {
	glutTimerFunc(MS_BETWEEN_FRAMES, timer, 0);

	prevTime = currTime;
	currTime = glutGet(GLUT_ELAPSED_TIME);
	elapsed = currTime - prevTime;

	glutPostRedisplay();
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
    unsigned int programID1 = LoadShaders("pf-light.vert", "pf-light.frag");
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

    //Disable back face rendering
    glEnable(GL_CULL_FACE);

    // wireframes for now
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // set up GLUT functions with associated application functions
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(render);
    glutReshapeFunc(reshapeWindow);

    glutTimerFunc(MS_BETWEEN_FRAMES, timer, 0);
    currTime = glutGet(GLUT_ELAPSED_TIME);

    std::cout << "W => move forwards, S => move backwards" << std::endl;
    std::cout << "A => strafe left, D => strafe right" << std::endl;
    std::cout << "Q => rotate left, E => rotate right" << std::endl;
    std::cout << "F to switch camera views" << std::endl;
    std::cout << "L to switch polygon mode" << std::endl;
    glutMainLoop();
    return 0;
}
