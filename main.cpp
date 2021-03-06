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
#include "LevelMap.hpp"
#include "Enemy.hpp"
#include "ParticleGenerator.hpp"
#include "Quad2D.hpp"
#include "libs/Lib.h"
#include "libs/sound.h"
#include "LevelMap.hpp"

#include <iostream>
#include <cstdlib>
#include <time.h>
//#include <string>

std::vector<unsigned int> programIDs;

// main section of objects
std::vector<Object> mainObjects;
std::vector<Enemy> enemies;
std::vector<Light> lights; // vector of light sources
std::vector<Camera> cameras;

bool collisionDetectionOn = true;
bool movementKeyPressed = false;

std::vector<ParticleGenerator> fires;

// objects relating to lava. Should just be the one item, but could add more if you like
std::vector<Object> lavaObjects;
Light lavaLight;

unsigned int lavaLightInitBrightness = 4.5;

// Mirrored surfaces
std::vector<Quad2D> mirrors;

// Statue/marble surfaces
std::vector<Object> statueObjects;

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
int objectSetup() {
    //Generate all level objects
    generateLevelMap(programIDs[0], mainObjects, lights);

    //Create enemies
    Enemy enemy(programIDs.at(0), "external_files/geom/cube-tex/cube-tex.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-2.5f, -0.2f, 9.5f), 0.1f);
    enemies.push_back(enemy);

    // Add mirror
    // Object mirror(programIDs[0], "external_files/geom/cube-simple/cube-simple.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-3.0f, 0.0f, 7.0f), 0.5f);
    Quad2D mirror(glm::vec3(-3.0, 0.0f, 7.0f), glm::vec3(0,0,0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 0.5f, programIDs[1]);
    mirrors.push_back(mirror);

	lavaLight = Light(glm::vec3(-7.5f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.3f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), lavaLightInitBrightness);

	glUseProgram(programIDs.at(0));

	player = new Player(programIDs.at(0), "external_files/geom/cube-tex/cube-tex.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.2f);

    camIdx = 0;
    Camera firstPerson = Camera();
    firstPerson.attachToObject(player, glm::vec3(0.0f, 0.0f, 0.01f));
    cameras.push_back(firstPerson);

    Camera thirdPerson = Camera();
    thirdPerson.attachToObject(player, glm::vec3(0.0f, 1.0f, -5.0f));
    cameras.push_back(thirdPerson);

	// create particle generators corresponding to each torch position
	ParticleGenerator p1(programIDs.at(1), glm::vec3(-3.5f, 0.1f, 2.63f), glm::vec3(0.0f), currTime);
	fires.push_back(p1);

	ParticleGenerator p2(programIDs.at(1), glm::vec3(1.40f, 0.1f, 5.1f), glm::vec3(0.0f, M_PI/2, 0.0f), currTime);
	fires.push_back(p2);

	ParticleGenerator p3(programIDs.at(1), glm::vec3(0.0f, 0.1f, 7.42f), glm::vec3(0.0f, 0.0f, 0.0f), currTime);
	fires.push_back(p3);

	ParticleGenerator p4(programIDs.at(1), glm::vec3(-5.0f, 0.1f, 7.40f), glm::vec3(0.0f), currTime); 
	fires.push_back(p4);

	ParticleGenerator p5(programIDs.at(1), glm::vec3(-2.5f, 0.1f, 10.40f), glm::vec3(0.0f), currTime);
	fires.push_back(p5);

	glUseProgram(programIDs.at(2));
    Object lava(programIDs[2], "external_files/geom/cube-simple/cube-simple.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-7.0f, -0.8f, 5.0f), 0.5f);
    lavaObjects.push_back(lava);

	glUseProgram(programIDs.at(3));
    //Add high poly model
    Object statue(programIDs[3], "external_files/geom/statue/statue.obj", glm::vec3(0.0f, M_PI/2.0, 0.0f), glm::vec3(-7.0f, 0.0f, 4.9f), 0.7f);
	statueObjects.push_back(statue);

    return 0;
}

/* Sets up all things that will be used frequently by the program - camera, mainObjects, etc.
 * Thus it should be called only once by the application, before any rendering is done. */
int setup() {
    setCamera();
    if (objectSetup() != 0) {
        return 1;
    }
    return 0;
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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

	// Render mirrors
	for (int i = 0; i < mirrors.size(); i++)
	{
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		mirrors.at(i).render();

		// Draw the reflected scene
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		// Get inverted camera matrix
		glm::mat4 savedCamMat = cameras.at(camIdx).getViewMatrix();
		cameras.at(camIdx).setViewMatrix(glm::scale(cameras.at(camIdx).getViewMatrix(), glm::vec3(1.0, 1.0, -1.0)));

		// Position lights in the reflected world
		// TODO: Reflect lighting

		glDisable(GL_DEPTH_TEST);
		/*
		 * Draw everything else
		 */
		// Render main objects (walls, floor, ect)
		cameras.at(camIdx).render(programIDs[0]);
		for (int j = 0; j < mainObjects.size(); j++){
			mainObjects.at(j).render(programIDs[0]);
		}

        for(int j = 0; j < enemies.size(); j++){
            enemies.at(j).render(programIDs[0]);
        }
		// draw particle generator 
		// we need to disable back face culling so that simple 2D squares will be correctly rendered.
		glDisable(GL_CULL_FACE);
		glUseProgram(programIDs.at(1));
		cameras.at(camIdx).render(programIDs.at(1));
		for (int j = 0; j < fires.size(); j++) {
			fires.at(j).render(programIDs.at(1), currTime);
		}
		glEnable(GL_CULL_FACE);
		/*
		 * Done rendering everything else
		 */

		// No more stencilling
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);

		// Reset Camera &  Lights
		cameras.at(camIdx).setViewMatrix(savedCamMat);
		// TODO: Undo lightning reflection

		// Render reflective surface
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mirrors.at(i).render();
		glDisable(GL_BLEND);
	}

	// render main objects
	glUseProgram(programIDs.at(0));
	//glGenerateMipmap(GL_TEXTURE_2D);

	int normMtxMainHandle = glGetUniformLocation(programIDs.at(0), "normal_matrix");
	if (normMtxMainHandle == -1) {
		std::cerr << "Could not find uniform variable 'normal_matrix'" << std::endl;
		exit(1);
	}
	
	int posMainHandle = glGetUniformLocation(programIDs.at(0), "lightPositions");
	int ambientMainHandle = glGetUniformLocation(programIDs.at(0), "lightAmbients");
	int diffuseMainHandle = glGetUniformLocation(programIDs.at(0), "lightDiffuses");
	int specularMainHandle = glGetUniformLocation(programIDs.at(0), "lightSpeculars");
	int brightnessMainHandle = glGetUniformLocation(programIDs.at(0), "lightBrightnesses");

	if ((posMainHandle == -1) || (ambientMainHandle == -1) || (diffuseMainHandle == -1) || (specularMainHandle == -1) || (brightnessMainHandle == -1)) {
		std::cerr << "Could not find light uniform variables." << std::endl;
		exit(1);
	}
	glUniform3fv(posMainHandle, lights.size(), glm::value_ptr(positions.front()));
	glUniform3fv(ambientMainHandle, lights.size(), glm::value_ptr(ambients.front()));
	glUniform3fv(diffuseMainHandle, lights.size(), glm::value_ptr(diffuses.front()));
	glUniform3fv(specularMainHandle, lights.size(), glm::value_ptr(speculars.front()));
	glUniform1fv(brightnessMainHandle, lights.size(), &brightnesses.front());

	cameras.at(camIdx).render(programIDs.at(0));
	glm::mat4 viewMtx = cameras.at(camIdx).getViewMatrix();

	for (int j = 0; j < mainObjects.size(); j++) {
		glm::mat3 normMtx = glm::transpose(glm::inverse(glm::mat3(mainObjects.at(j).getModelMatrix() * viewMtx))); 
		glUniformMatrix3fv(normMtxMainHandle, 1, false, glm::value_ptr(normMtx));
		mainObjects.at(j).render(programIDs.at(0));    
	}
	for(int j = 0; j < enemies.size(); j++){
		glm::mat3 normMtx = glm::transpose(glm::inverse(glm::mat3(mainObjects.at(j).getModelMatrix() * viewMtx))); 
		glUniformMatrix3fv(normMtxMainHandle, 1, false, glm::value_ptr(normMtx));
		enemies.at(j).render(programIDs[0]);
	}
    player->render(programIDs.at(0));

	lights.erase(lights.end()); // remove the lava light source from the lights again


	// draw particle generator 
	// we need to disable back face culling so that simple 2D squares will be correctly rendered.
    glDisable(GL_CULL_FACE);
	glUseProgram(programIDs.at(1));

	cameras.at(camIdx).render(programIDs.at(1));

	for (int i = 0; i < fires.size(); i++) {
		fires.at(i).render(programIDs.at(1), currTime);
	}
    glEnable(GL_CULL_FACE);
	

	// render lava floor
	glUseProgram(programIDs.at(2));
	int timerHandle = glGetUniformLocation(programIDs.at(2), "program_time");
	if (timerHandle == -1) {
		std::cerr << "Could not find uniform procedural texture variable 'program_time'" << std::endl;
		exit(1);
	}

	int normMtxLavaHandle = glGetUniformLocation(programIDs.at(2), "normal_matrix");
	if (normMtxLavaHandle == -1) {
		std::cerr << "Could not find uniform variable 'normal_matrix'" << std::endl;
		exit(1);
	}
	
	int posLavaHandle = glGetUniformLocation(programIDs.at(2), "lightPositions");
	int ambientLavaHandle = glGetUniformLocation(programIDs.at(2), "lightAmbients");
	int diffuseLavaHandle = glGetUniformLocation(programIDs.at(2), "lightDiffuses");
	int specularLavaHandle = glGetUniformLocation(programIDs.at(2), "lightSpeculars");
	int brightnessLavaHandle = glGetUniformLocation(programIDs.at(2), "lightBrightnesses");

	if ((posLavaHandle == -1) || (ambientLavaHandle == -1) || (diffuseLavaHandle == -1) || (specularLavaHandle == -1) || (brightnessLavaHandle == -1)) {
		std::cerr << "Could not find light uniform variables." << std::endl;
		exit(1);
	}
	glUniform3fv(posLavaHandle, lights.size(), glm::value_ptr(positions.front()));
	glUniform3fv(ambientLavaHandle, lights.size(), glm::value_ptr(ambients.front()));
	glUniform3fv(diffuseLavaHandle, lights.size(), glm::value_ptr(diffuses.front()));
	glUniform3fv(specularLavaHandle, lights.size(), glm::value_ptr(speculars.front()));
	glUniform1fv(brightnessLavaHandle, lights.size(), &brightnesses.front());
	cameras.at(camIdx).render(programIDs.at(2));
	glUniform1i(timerHandle, currTime);
	for (int j = 0; j < lavaObjects.size(); j++) {
		glm::mat3 normMtx = glm::transpose(glm::inverse(glm::mat3(lavaObjects.at(j).getModelMatrix() * viewMtx))); 
		glUniformMatrix3fv(normMtxMainHandle, 1, false, glm::value_ptr(normMtx));
		lavaObjects.at(j).render(programIDs.at(2));
	}


	glUseProgram(programIDs.at(3));

	// render statue
	int normMtxStatueHandle = glGetUniformLocation(programIDs.at(3), "normal_matrix");
	if (normMtxStatueHandle == -1) {
		std::cerr << "Could not find uniform variable 'normal_matrix'" << std::endl;
		exit(1);
	}
	
	int posStatueHandle = glGetUniformLocation(programIDs.at(3), "lightPositions");
	int ambientStatueHandle = glGetUniformLocation(programIDs.at(3), "lightAmbients");
	int diffuseStatueHandle = glGetUniformLocation(programIDs.at(3), "lightDiffuses");
	int specularStatueHandle = glGetUniformLocation(programIDs.at(3), "lightSpeculars");
	int brightnessStatueHandle = glGetUniformLocation(programIDs.at(3), "lightBrightnesses");

	if ((posStatueHandle == -1) || (ambientStatueHandle == -1) || (diffuseStatueHandle == -1) || (specularStatueHandle == -1) || (brightnessStatueHandle == -1)) {
		std::cerr << "Could not find light uniform variables." << std::endl;
		exit(1);
	}
	glUniform3fv(posStatueHandle, lights.size(), glm::value_ptr(positions.front()));
	glUniform3fv(ambientStatueHandle, lights.size(), glm::value_ptr(ambients.front()));
	glUniform3fv(diffuseStatueHandle, lights.size(), glm::value_ptr(diffuses.front()));
	glUniform3fv(specularStatueHandle, lights.size(), glm::value_ptr(speculars.front()));
	glUniform1fv(brightnessStatueHandle, lights.size(), &brightnesses.front());
	cameras.at(camIdx).render(programIDs.at(3));
	for (int j = 0; j < statueObjects.size(); j++) {
		glm::mat3 normMtx = glm::transpose(glm::inverse(glm::mat3(statueObjects.at(j).getModelMatrix() * viewMtx))); 
		glUniformMatrix3fv(normMtxMainHandle, 1, false, glm::value_ptr(normMtx));
		statueObjects.at(j).render(programIDs.at(3));
	}

    glutSwapBuffers();
    glFlush();
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Esc
            exit(1);
            break;
        case 'a':
            if(!player->checkCollision(collisionDetectionOn, mainObjects)){
                movementKeyPressed = true;
                player->strafeLeft();
                glutPostRedisplay();
            }
            else{
                player->setPrevPos();
                playSound("external_files/sounds/bong.wav");
            }
            break;
        case 'd':
            if(!player->checkCollision(collisionDetectionOn, mainObjects)){
                movementKeyPressed = true;
                player->strafeRight();
                glutPostRedisplay();
            }
            else{
                player->setPrevPos();
                playSound("external_files/sounds/bong.wav");
            }
            break;
        case 'q':
            if(!player->checkCollision(collisionDetectionOn, mainObjects)){
                movementKeyPressed = true;
                player->rotLeft();
                glutPostRedisplay();
            }
            else{
                player->setPrevPos();
                playSound("external_files/sounds/bong.wav");
            }
            break;
        case 'e':
            if(!player->checkCollision(collisionDetectionOn, mainObjects)){
                movementKeyPressed = true;
                player->rotRight();
                glutPostRedisplay();
            }
            else{
                player->setPrevPos();
                playSound("external_files/sounds/bong.wav");
            }
            break;
        case 'w':
            if(!player->checkCollision(collisionDetectionOn, mainObjects)){
                movementKeyPressed = true;
                player->moveForward();
                glutPostRedisplay();
            }
            else{
                player->setPrevPos();
                playSound("external_files/sounds/bong.wav");
            }
            break;
        case 's':
            if(!player->checkCollision(collisionDetectionOn, mainObjects)){
                movementKeyPressed = true;
                player->moveBackward();
                glutPostRedisplay();
            }
            else{
                player->setPrevPos();
                playSound("external_files/sounds/bong.wav");
            }
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
		case '\\': // press backslash to toggle collision detection.
			collisionDetectionOn = !collisionDetectionOn;
			glutPostRedisplay();
			break;
    }
}

void keyboardUpFunc(unsigned char key, int x, int y){
    switch(key){
        case 'w':
            movementKeyPressed = false;
            player->stopMovement();
            break;        
        case 'a':
            movementKeyPressed = false;
            player->stopMovement();
            break;
        case 's':
            movementKeyPressed = false;
            player->stopMovement();
            break;
        case 'd':
            movementKeyPressed = false;
            player->stopMovement();
            break;
        case 'q':
            movementKeyPressed = false;
            player->stopMovement();
            break;
        case 'e':
            movementKeyPressed = false;
            player->stopMovement();
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

    player->idleMovement();

    for(unsigned i = 0; i < enemies.size(); i++){
        enemies.at(i).update(collisionDetectionOn, mainObjects);
    }

	prevTime = currTime;
	currTime = glutGet(GLUT_ELAPSED_TIME);
	elapsed = currTime - prevTime;
 
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	srand(time(NULL));

    // Set up basic window management stuff.
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutCreateWindow("Computer Graphics, S1 2015 - Assignment 3");

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialise GLEW." << std::endl;
        return -1;
    }

    // load and compile shader files
    unsigned int mainProgramID = LoadShaders("pf-light.vert", "pf-light.frag");
    if (mainProgramID == 0) {
        return 1;
    }
	programIDs.push_back(mainProgramID);

	unsigned int particleProgramID = LoadShaders("particle.vert", "particle.frag");
	if (particleProgramID == 0) {
	    return 1;
	}
	programIDs.push_back(particleProgramID);

	unsigned int lavaProgramID = LoadShaders("lava.vert", "lava.frag");
	if (lavaProgramID == 0) {
	    return 1;
	}
	programIDs.push_back(lavaProgramID);

	unsigned int statueProgramID = LoadShaders("statue.vert", "statue.frag");
	if (statueProgramID == 0) {
	    return 1;
	}
	programIDs.push_back(statueProgramID);

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
    glutKeyboardUpFunc(keyboardUpFunc);
    glutSpecialFunc(specialFunc);
    glutMouseFunc(mouseFunc);
    glutDisplayFunc(render);
    glutReshapeFunc(reshapeWindow);

    glutTimerFunc(MS_BETWEEN_FRAMES, timer, 0);
    currTime = glutGet(GLUT_ELAPSED_TIME);

    if (setup() != 0) {
        std::cerr << "setup() failed." << std::endl;
        return 1;
    }

    std::cout << "W => move forwards, S => move backwards" << std::endl;
    std::cout << "A => strafe left, D => strafe right" << std::endl;
    std::cout << "Q => rotate left, E => rotate right" << std::endl << std::endl;
    std::cout << "Use \\ to disable collision detection" << std::endl << std::endl;
    std::cout << "F to switch camera views" << std::endl;
    std::cout << "L to switch polygon mode" << std::endl;
    glutMainLoop();
    return 0;
}
