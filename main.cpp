#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.hpp"
#include "Object.hpp"
#include "libs/Lib.h"

#include <iostream>
#include <cstdlib>
//#include <string>

unsigned int programID;
std::vector<Object*> objects;

double FOV = 45.0;

void setCamera() {
    glm::mat4 projection;
    projection = glm::infinitePerspective(FOV, double(WINDOW_WIDTH)/double(WINDOW_HEIGHT), 1.0);

    int projHandle = glGetUniformLocation(programID, "projection_matrix");
    if (projHandle == -1) {
        std::cerr << "'projection_matrix' is not an active uniform label." << std::endl;
        exit(1);
    }
    glUniformMatrix4fv(projHandle, 1, false, glm::value_ptr(projection));
}

/* Set up all required objects etc.
 * Returns 0 on success, nonzero otherwise. */
int objectSetup() {
    Object* tet = new Object("geom/tetra/tetra.obj", programID);
    objects.push_back(tet);

    Object* cube = new Object("geom/cube-simple/cube-simple.obj", programID);
    objects.push_back(cube);
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
    glUseProgram(programID);

    glm::mat4 viewMatrix;
    viewMatrix = glm::lookAt(glm::vec3(0.0f, 4.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    for (int i = 0; i < objects.size(); i++) {
        objects.at(i)->render(programID, viewMatrix);
    }

    //glutSwapBuffers();
    glFlush();
}

void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
        case 'q':
            exit(0);
            break;
            /*
        case 's':
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
            */

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
    programID = LoadShaders("wireframe.vert", "wireframe.frag");
    if (programID == 0) {
        return 1;
    }
    glUseProgram(programID);

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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // set up GLUT functions with associated application functions
    glutKeyboardFunc(keyboardFunc);
    glutDisplayFunc(render);

    glutMainLoop();
    return 0;
}
