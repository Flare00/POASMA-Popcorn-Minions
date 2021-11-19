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
#include <string>

#include "header/Vec3.h"
//#include "header/Camera.h"
//#include "header/Drawgrid.h"
#include "header/Simulation.h"


using namespace std;
bool isSubstateOf(StateEnum state, SubStateEnum subState) {
	bool result = false;
	switch (state) {
	case StateEnum::empty:
	case StateEnum::exitDoor:
	case StateEnum::popCorn:
	case StateEnum::flame:
		if (subState == SubStateEnum::subEmpty) {
			result = true;
		}
		break;
	case StateEnum::wall:
		if (subState == SubStateEnum::subEmpty || subState == SubStateEnum::wallWood) {
			result = true;
		}
		break;
	case StateEnum::minion:
		if (subState == SubStateEnum::subEmpty || subState == SubStateEnum::pompier || subState == SubStateEnum::pyroman) {
			result = true;
		}
		break;

	}
	return result;
}
/*chrono::high_resolution_clock::time_point last = chrono::high_resolution_clock::now();

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
}*/

int main(int argc, char** argv) {
	srand(time(NULL));
	/*if (argc > 2) {
		exit(EXIT_FAILURE);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	window = glutCreateWindow("Popcorn Minions");

	bat = new Batiment(30, 30,30 , 4, 1 ,300);

	init();
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutReshapeFunc(reshape);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	key('?', 0, 0);

	glutMainLoop();
	delete bat;*/
	Simulation* s = new Simulation();
	Batiment* b = s->getBatiment();
	vector<Etage*> etages = b->getEtages();
	for (int i = 0, max = etages.size(); i < max; i++) {
		Etage* e = etages[i];
		for (int x = 0; x < 10; x++) {
			string ligne = "";

			for (int y = 0; y < 10; y++) {
				Case* c = e->getCase(x, y);
				switch (c->getState()) {
				case StateEnum::empty:
					ligne += "   ";
					break;
				case StateEnum::wall:
					if (isSubstateOf(c->getState(), c->getSubState())) {
						if (c->getSubState() == SubStateEnum::wallWood) {
							ligne += " w ";
						}
						else {
							ligne += " W ";
						}
					}
					else {
						ligne += " X ";
					}
					break;
				case StateEnum::flame:
					ligne += " F ";
					break;
				case StateEnum::minion:
					if (isSubstateOf(c->getState(), c->getSubState())) {
						if (c->getSubState() == SubStateEnum::pompier) {
							ligne += " p ";
						}
						else if (c->getSubState() == SubStateEnum::pyroman) {
							ligne += " P ";
						}
						else {
							ligne += " M ";
						}
					}
					else {
						ligne += " X ";
					}
					break;
				case StateEnum::enterDoor:
					ligne += " e ";
					break;
				case StateEnum::exitDoor:
					ligne += " E ";

					break;
				case StateEnum::popCorn:
					ligne += " C ";
					break;
				}
			}
			cout << ligne << endl;
		}
		cout << endl << "------"  << endl << endl;
	}

	delete s;
	return EXIT_SUCCESS;
}