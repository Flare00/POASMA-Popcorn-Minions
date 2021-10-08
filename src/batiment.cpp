#include "batiment.h"
#include "stateEnum.h"
#include <cstddef>
	Batiment::Batiment(int x, int y){
		this->width = x;
		this->height = y;
		this->grid = new Case*[this->width];
		for(int i = 0; i < this->width; i++){
			grid[i] = new Case[this->height];
		}
	}
	Batiment::~Batiment(){
		for(int i = 0; i < this->width; i++){
			delete grid[i];
		}
		delete grid;
	}

	bool Batiment::fire(int x, int y){    //is there fire in (x,y)
		return this->grid[x][y].getState() == StateEnum::flame;
	}
	int* Batiment::getExitDoors(){ //fill the tab "tab" and set n to the number of exit
		return NULL;
	}

	bool Batiment::flamable(int x, int y){
		return false;
	}
	Case* Batiment::getCase(int x, int y){
		return &this->grid[x][y];
	}
	Case** Batiment::getGrid(){
		return this->grid;
	}