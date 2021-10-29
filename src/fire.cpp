#include "fire.h"
#include "batiment.h"
#include "minion.h"
#include <cstddef>
#include <stdlib.h>
#include <time.h>

#define PROPAGATION_CHANCE 3
Fire::Fire(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}
void Fire::action(Batiment * batiment){
	if(pauseUnTour){
		this->pauseUnTour = false;
	} else {
		if (rand() % PROPAGATION_CHANCE == 0) {
			this->propagate(batiment->getCase(this->getX() - 1, this->getY()) ,batiment);
		}

		if (rand() % PROPAGATION_CHANCE == 0) {
			this->propagate(batiment->getCase(this->getX() + 1, this->getY()),batiment);
		}
		if (rand() % PROPAGATION_CHANCE == 0) {
			this->propagate(batiment->getCase(this->getX(), this->getY() - 1),batiment);
		}
		if (rand() % PROPAGATION_CHANCE == 0) {
			this->propagate(batiment->getCase(this->getX(), this->getY() + 1),batiment);
		}	
	}
}

void Fire::propagate(Case * emplacement,Batiment * batiment){
	if(emplacement != NULL){
		bool fire = false;
		switch(emplacement->getState()){
			case StateEnum::minion : 
				emplacement->setState(StateEnum::popCorn);
				((Minion*)emplacement->getAgent())->popcorn();
				//batiment->escapeMinion(); // He escaped to heaven, press F
				batiment->burnedMinion();
				if(batiment->getRemainingMinions()==0)
					exit(0);
				break;
			case StateEnum::empty :
			case StateEnum::wallWood :
				emplacement->setState(StateEnum::flame);
				emplacement->setAgent(new Fire(emplacement->getX(), emplacement->getY()));
				break;
		}
	}
}

void Fire::pause(){
	this->pauseUnTour=true;
}


