#include "batiment.h"
#include "fire.h"
#include "stateEnum.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstddef>
#include <time.h>
#include <ostream>
	Batiment::Batiment(int x, int y, int start_nbminion, int start_nbfire, int nb_exits, int nb_wall){
		this->start_nbminion = start_nbminion;
		this->start_nbfire = start_nbfire;
		this->nb_exits = nb_exits;
		this->width = x;
		this->height = y;
		this->grid = new Case**[this->width];
		
		for(int i = 0; i < this->width; i++){
			grid[i] = new Case*[this->height];
			for(int j = 0; j < this->height;j++){
				grid[i][j] = new Case(i,j);
			}
		}
		srand(time(NULL));
		int putted = 0;
		while(putted < nb_exits){
			int i = rand()%x;
			int j = rand()%y;
			if(grid[i][j]->getState() == StateEnum::empty){
				grid[i][j]->setState(StateEnum::exitDoor);
				putted++;
			}
		}
		putted = 0;
		while(putted < nb_wall){
			int i = rand()%x;
			int j = rand()%y;
			if(grid[i][j]->getState() == StateEnum::empty){
				grid[i][j]->setState( StateEnum::wall);
				putted++;
			}
		}
		putted = 0;
		while(putted < start_nbminion){
			int i = rand()%x;
			int j = rand()%y;
			if(grid[i][j]->getState() == StateEnum::empty){
				grid[i][j]->setState( StateEnum::minion);
				//grid[i][j]->setAgent(new Minion());
				putted++;
			}
		}
		putted = 0;
		while(putted < start_nbfire){
			int i = rand()%x;
			int j = rand()%y;
			if(grid[i][j]->getState() == StateEnum::empty){
				grid[i][j]->setState( StateEnum::flame);
				
				grid[i][j]->setAgent((Agent*)new Fire(i,j));
				putted++;
			}
		}

		
	}
	
	Batiment::~Batiment(){
		for(int i = 0; i < this->width; i++){
			for(int j = 0; j < this->height; j++){
				if(grid[i][j]->getAgent() != NULL){
					delete grid[i][j]->getAgent();
				}
				delete grid[i][j];
			}
			delete grid[i];
		}
		delete grid;
	}

	StateEnum Batiment::getState(int x, int y){
		return this->getCase(x,y)->getState();
	}
	Case** Batiment::getExitDoors(){
		Case ** res = new Case*[this->nb_exits];
		int found = 0;
		for(int i = 0; i < this->width && found < nb_exits ; i++){
			for(int j = 0; j < this->height && found < nb_exits ; j++){
				if(this->grid[i][j]->getState() == StateEnum::exitDoor){
					res[found] = this->grid[i][j];
					found++;
				}
			}
		}
		return res;
	}

	Case* Batiment::getCase(int x, int y){
		return this->grid[x][y];
	}
	Case*** Batiment::getGrid(){
		return this->grid;
	}
	
	int Batiment::getWidth(){
		return this->width;
	}
	int Batiment::getHeight(){
		return this->height;
	}
