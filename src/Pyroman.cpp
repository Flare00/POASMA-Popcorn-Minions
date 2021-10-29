#include"pyroman.h"
#include "batiment.h"
#include "minion.h"
#include "case.h"
#include "fire.h"
#include <iostream>
using namespace std;
Pyroman::Pyroman(int x,int y):Minion(x,y){}


void Pyroman::move(Batiment* batiment, int x, int y){
	Case* emplacement = batiment->getCase(x,y); //la position donnée en entrer
	if (emplacement != NULL) {
		Case* currentCase = batiment->getCase(this->getX(), this->getY());// ma position actuelle qui change  
		switch (emplacement->getState()) {
			case StateEnum::empty :
				emplacement->setState(StateEnum::pyroman);
				emplacement->setAgent(this);
				this->setX(x);
				this->setY(y);
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
				break;
			case StateEnum::flame :
				emplacement->setState(StateEnum::popCorn);
				delete emplacement->getAgent();
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
				delete this;
				break;
		}
	}
}


void Pyroman::action(Batiment* batiment){
	int x = this->getX();
	int y = this->getY();

	this->flagPyroman = true;
	Fire* f;


	int deplacementX = (rand() % 2 == 0) ? -1 : 1;
	int deplacementY = (rand() % 2 == 0) ? -1 : 1;
	int direction = (rand() % 2);
	//diagonales
	//this->move(batiment, this->getX() + deplacementX, this->getY() + deplacementY);
	//haut bas 
	if (direction == 0) {	
		this->move(batiment, this->getX(), this->getY() + deplacementY);
		f->Fire::action(batiment);
	}
	else{
		this->move(batiment, this->getX() + deplacementX, this->getY());	
		f->Fire::action(batiment);
	}
}