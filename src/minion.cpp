#include "minion.h"
#include "case.h"
#include "batiment.h"

Minion::Minion(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}
void Minion::action(Batiment* batiment){
	Case* emplacement = batiment->getCase(this->getX(), this->getY());
	int x = this->getX();
	int y = this->getY();


	Case** exitDoors = batiment->getExitDoors();
	Case* closestExit = exitDoors[0];

	// TODO je sais pas comment connaitre la taille du tableau ?
	for (int i = 0; i < 1; ++i) 
	{
		if(Case::distaceHamilton(exitDoors[i],emplacement)<Case::distaceHamilton(closestExit,emplacement)){
			closestExit = exitDoors[i];
		}
	}

	this->moveToward(batiment, closestExit);
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
				break;
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

void Minion::moveToward(Batiment* batiment, Case * c){
	int dx = 0;
	int dy = 0;

	if(c->getX()>this->getX()){
		dx = 1;
	}else if(c->getX()<this->getX()){
		dx = -1;
	}

	if(c->getY()>this->getY()){
		dy = 1;
	}else if(c->getY()<this->getY()){
		dy = -1;
	}
	this->move(batiment, dx, dy);
}