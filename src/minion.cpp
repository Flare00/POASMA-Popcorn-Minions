
#ifndef includes
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
#include <cstddef>
#include <ctime>

#include "batiment.h"
#include "fire.h"
#include "stateEnum.h"
#include "minion.h"
#include "case.h"

#endif

using namespace std;
Minion::Minion(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}
void Minion::action(Batiment* batiment){
/*	StateEnum type = batiment->getState(x,y);

			switch ( type )
			{
				case StateEnum::wall:
					drawWall(xpos,ypos,tilesize,1);
					break;
				case StateEnum::minion:
					drawMinion(xpos,ypos,tilesize,1);
					break;
				case StateEnum::flame:
					drawFire(xpos,ypos,tilesize,1);
					break;
				case StateEnum::exitDoor:
					drawExit(xpos,ypos,tilesize,1);
					break;
					
			}*/

	//Case** Batiment::getExitDoors(){
	//int Case::getX(){

	//Case ** exitDoors = batiment.getExitDoors();

}
void Minion::move(Batiment* batiment, int deltaX, int deltaY){
	Case* emplacement = batiment->getCase(this->getX() + deltaX, this->getY() + deltaY);
	if (emplacement != NULL) {
		Case* currentCase = batiment->getCase(this->getX(), this->getY());
		switch (emplacement->getState()) {
			case StateEnum::empty :
				emplacement->setState(StateEnum::minion);
				emplacement->setAgent(this);
				this->setX(this->getX() + deltaX);
				this->setY(this->getY() + deltaY);
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
			case StateEnum::flame :
				emplacement->setState(StateEnum::popCorn);
				delete emplacement->getAgent();
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
				delete this;
				break;
			case StateEnum::exitDoor :
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
				delete this;
				break;
		}
	}
}
void Minion::idle(){
	
}
void Minion::panik(Batiment* batiment){
	srand(time(NULL));
	int deplacement = (rand() % 2 == 0) ? -1 : 1;
	int direction = (rand() % 2);
	if (direction == 0) {
		this->move(batiment, deplacement, 0);
	}
	else {
		this->move(batiment, 0, deplacement);
	}

}
void Minion::popcorn(){
	delete this;
}