#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#include "header/Vec3.h"
#include "header/Camera.h"
#include "header/Drawgrid.h"
#include "header/batiment.h"

using namespace std;

chrono::high_resolution_clock::time_point last = chrono::high_resolution_clock::now();

long int nextUpdate = 0;

Batiment* bat;

static GLint window;
static unsigned int SCREENWIDTH = 1600;
static unsigned int SCREENHEIGHT = 900;
static Camera camera;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX = 0, lastY = 0, lastZoom = 0;

void initLight() {
	GLfloat light_position1[4] = { 22.0f, 16.0f, 50.0f, 0.0f };
	GLfloat direction1[3] = { -52.0f,-16.0f,-50.0f };
	GLfloat color1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambient[4] = { 0.3f, 0.3f, 0.3f, 0.5f };

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, color1);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}

void init() {
	camera.resize(SCREENWIDTH, SCREENHEIGHT);
	initLight();
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
	glEnable(GL_COLOR_MATERIAL);

	glDisable(GL_CULL_FACE);
}

void draw() {
    long long int duration = (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-last)).count(); 

    if(duration>= 1000){
        last = chrono::high_resolution_clock::now();
        bat->doAction();
    }
    drawGrid(bat);
}


void display() {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.apply();
    draw();
    glFlush();
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

void key(unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
    case '1': //Je garde ça au cas où...
        //do stuff
        break;

    default:
        break;
    }
    idle();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    }
    else {
        if (button == GLUT_LEFT_BUTTON) {
            camera.beginRotate(x, y);
            mouseMovePressed = false;
            mouseRotatePressed = true;
            mouseZoomPressed = false;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            lastX = x;
            lastY = y;
            mouseMovePressed = true;
            mouseRotatePressed = false;
            mouseZoomPressed = false;
        }
        else if (button == GLUT_MIDDLE_BUTTON) {
            if (mouseZoomPressed == false) {
                lastZoom = y;
                mouseMovePressed = false;
                mouseRotatePressed = false;
                mouseZoomPressed = true;
            }
        }
    }
    idle();
}

void motion(int x, int y) {
    if (mouseRotatePressed == true) {
        camera.rotate(x, y);
    }
    else if (mouseMovePressed == true) {
        camera.move((x - lastX) / static_cast<float>(SCREENWIDTH), (lastY - y) / static_cast<float>(SCREENHEIGHT), 0.0);
        lastX = x;
        lastY = y;
    }
    else if (mouseZoomPressed == true) {
        camera.zoom(float(y - lastZoom) / SCREENHEIGHT);
        lastZoom = y;
    }
}


void reshape(int w, int h) {
    camera.resize(w, h);
}

int main(int argc,char** argv){
    srand(time(NULL));
    if (argc > 2) {
        exit(EXIT_FAILURE);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
    window = glutCreateWindow("Popcorn Minions");

    bat = new Batiment(30, 30,30 , 4, 1 ,200);

    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    key('?', 0, 0);

    glutMainLoop();
    delete bat;
    return EXIT_SUCCESS;
}

