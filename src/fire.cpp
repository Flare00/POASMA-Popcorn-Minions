#include "fire.h"
#include "batiment.h"
#include "minion.h"
#include <cstddef>
Fire::Fire(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}
void Fire::action(Batiment * batiment){
	this->propagate(batiment->getCase(this->getX()-1, this->getY()));
	this->propagate(batiment->getCase(this->getX()+1, this->getY()));
	this->propagate(batiment->getCase(this->getX(), this->getY()-1));
	this->propagate(batiment->getCase(this->getX(), this->getY()+1));
}

void Fire::propagate(Case * emplacement){
	if(emplacement != NULL){
		bool fire = false;
		switch(emplacement->getState()){
			case StateEnum::minion : 
				((Minion*)emplacement->getAgent())->popcorn();
			case StateEnum::empty :
				fire = true;
				break;
		}
		if(fire){
			emplacement->setState(StateEnum::flame);
			emplacement->setAgent(new Fire(emplacement->getX(),emplacement->getY()));
		}
	}
}