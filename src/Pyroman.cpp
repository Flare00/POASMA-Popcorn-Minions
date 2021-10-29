#include"pyroman.h"
#include "batiment.h"
#include "minion.h"
#include "case.h"
#include "fire.h"
#include <iostream>
using namespace std;
Pyroman::Pyroman(int x,int y):Minion(x,y){}


bool Pyroman::move(Batiment* batiment, int x, int y){
	bool moved = false;
	Case* emplacement = batiment->getCase(x,y); //la position donnée en entrer
	if (emplacement != NULL) {
		Case* currentCase = batiment->getCase(this->getX(), this->getY());// ma position actuelle qui change  
		switch (emplacement->getState()) {
			case StateEnum::empty :
							moved=true;
				emplacement->setState(StateEnum::pyroman);
				emplacement->setAgent(this);
				this->setX(x);
				this->setY(y);
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
				break;
			case StateEnum::flame :
				moved = true;
				delete emplacement->getAgent();
				emplacement->setState(StateEnum::pyroman);
				emplacement->setAgent(this);
				this->setX(x);
				this->setY(y);
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
		}
	}
	return moved;
}


void Pyroman::action(Batiment* batiment){

	Fire* f;

	int deplacement = (rand() % 2 == 0) ? -1 : 1;
	int direction = (rand() % 4);
	bool moved = false;

	Case * emplacement = batiment->getCase(this->getX(), this->getY());
	switch(direction){
		case 0:
			moved=this->move(batiment, this->getX(),this->getY()+1);
		break;
		case 1:
			moved=this->move(batiment, this->getX()+1,this->getY());
		break;
		case 2:
			moved=this->move(batiment, this->getX(),this->getY()-1);
		break;
		case 3:
			moved=this->move(batiment, this->getX()-1,this->getY());
		break;
	}
	if(moved){
		emplacement->setState(StateEnum::flame);
		f = new Fire(emplacement->getX(), emplacement->getY());
		emplacement->setAgent(f);
		f->pause();
	}
}