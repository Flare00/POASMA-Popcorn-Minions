#include "minion.h"
#include "case.h"
Minion::Minion(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}
void Minion::action(Batiment* batiment){
	
}
void Minion::move(Batiment* batiment, int deltaX, int deltaY){
	Case* emplacement = batiment->getCase(this->getX() + deltaX, this->getY() + deltaY);
	if (emplacement != NULL) {
		Case* currentCase = batiment->getCase(this->getX(), this->getY);
		switch (emplacement->getStatement()) {
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