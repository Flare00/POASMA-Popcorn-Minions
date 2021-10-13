#include "fire.h"
#include "batiment.h"
#include "minion.h"
#include <cstddef>
#include <stdlib.h>
#include <time.h>
#define PROPAGATION_CHANCE 100
Fire::Fire(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}
void Fire::action(Batiment * batiment){
	srand(time(NULL));
	if (rand() % PROPAGATION_CHANCE == 0) {
		this->propagate(batiment->getCase(this->getX() - 1, this->getY()));
	}
	if (rand() % PROPAGATION_CHANCE == 0) {
		this->propagate(batiment->getCase(this->getX() + 1, this->getY()));
	}
	if (rand() % PROPAGATION_CHANCE == 0) {
		this->propagate(batiment->getCase(this->getX(), this->getY() - 1));
	}
	if (rand() % PROPAGATION_CHANCE == 0) {
		this->propagate(batiment->getCase(this->getX(), this->getY() + 1));
	}
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