#include <cstddef>
#include <stdlib.h>
#include <time.h>

#include "fire.h"

#define PROPAGATION_CHANCE 3
Fire::Fire(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}
void Fire::action(Etage * etage){
	if(pauseUnTour){
		this->pauseUnTour = false;
	} else {
		if (rand() % PROPAGATION_CHANCE == 0) {
			this->propagate(etage->getCase(this->getX() - 1, this->getY()) ,etage);
		}

		if (rand() % PROPAGATION_CHANCE == 0) {
			this->propagate(etage->getCase(this->getX() + 1, this->getY()),etage);
		}
		if (rand() % PROPAGATION_CHANCE == 0) {
			this->propagate(etage->getCase(this->getX(), this->getY() - 1),etage);
		}
		if (rand() % PROPAGATION_CHANCE == 0) {
			this->propagate(etage->getCase(this->getX(), this->getY() + 1),etage);
		}	
	}
}

void Fire::propagate(Case * emplacement, Etage* etage){
	if(emplacement != NULL){
		bool fire = false;
		switch(emplacement->getState()){
			case StateEnum::minion : 
				emplacement->setState(StateEnum::popCorn);
				((Minion*)emplacement->getAgent())->popcorn();
				//etage->escapeMinion(); // He escaped to heaven, press F
				etage->burnedMinion();
				if(etage->getRemainingMinions()==0)
					exit(0);
				break;
			case StateEnum::empty :
			case StateEnum::wall :
				if (emplacement->getSubState() == SubStateEnum::wallWood) {
					emplacement->setState(StateEnum::flame);
					emplacement->setAgent(new Fire(emplacement->getX(), emplacement->getY()));
				}
				break;
		}
	}
}

void Fire::pause(){
	this->pauseUnTour=true;
}


