#include "batiment.h"
#include "fire.h"
#include "stateEnum.h"
#include "minion.h"
#include "pompier.h"
#include "pyroman.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstddef>
#include <time.h>
#include <iostream>
#include <vector>


	Batiment::Batiment(int x, int y, int start_nbminion, int start_nbfire,int start_nbPompier,int start_nbPyroman, int nb_exits, int nb_wall){
		this->escapedMinion = 0;
		this->start_nbminion = start_nbminion;
		this->start_nbfire = start_nbfire;

		this->start_nbPompier=start_nbPompier;
		this->start_nbPyroman=start_nbPyroman;

		this->nb_exits = nb_exits;
		this->width = x;
		this->height = y;
		this->grid = new Case**[this->width];
		
		for(int i = 0; i < this->width; i++){
			grid[i] = new Case*[this->height];
			for(int j = 0; j < this->height;j++){
				grid[i][j] = new Case(i,j);
				grid[i][j]->setState(StateEnum::empty);
			}
		}
//		srand(time(NULL));
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
				grid[i][j]->setAgent((Agent*)new Minion(i,j));
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
		//Pompier
		putted = 0;
		while(putted < start_nbPompier){
			int i = rand()%x;
			int j = rand()%y;
			if(grid[i][j]->getState() == StateEnum::empty){
				grid[i][j]->setState( StateEnum::pompier);
				
				grid[i][j]->setAgent((Agent*)new Pompier(i,j));
				putted++;
			}
		}
		//Pyroman
		putted = 0;
		while(putted < start_nbPyroman){
			int i = rand()%x;
			int j = rand()%y;
			if(grid[i][j]->getState() == StateEnum::empty){
				grid[i][j]->setState(StateEnum::pyroman);
				
				grid[i][j]->setAgent((Agent*)new Pyroman(i,j));
				putted++;
			}
		}
		
	}
	
	Batiment::~Batiment(){
		for(int i = 0; i < this->width; i++){
			for(int j = 0; j < this->height; j++){
				delete grid[i][j];
			}
			delete grid[i];
		}
		delete grid;
	}

	StateEnum Batiment::getState(int x, int y){
		return this->getCase(x,y)->getState();
	}
	std::vector<Case *> Batiment::getExitDoors(){
		std::vector<Case *> res;// = new Case*[this->nb_exits];
		res.resize(this->nb_exits);
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
	void  Batiment::escapeMinion()
	{
		this->escapedMinion++;
		this->start_nbminion--;
		std::cout<<"Nombre de minions qui se sont échapés depuis le début des temps : "<<this->escapedMinion<<std::endl;
	}
	void  Batiment::burnedMinion()
	{
		this->start_nbminion--;
	}
	int Batiment::getRemainingMinions()
	{
		return this->start_nbminion;
	}


	Case* Batiment::getCase(int x, int y){

		return (x >= 0 && x < width && y >= 0 && y < height) ? this->grid[x][y] : NULL;
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

	void Batiment::doAction()
	{
		std::vector<Agent*> minions;
		std::vector<Agent*> fires;
		
		std::vector<Agent*> pompier;
		std::vector<Agent*> pyroman;

		for(int i = 0; i < this->getWidth() ; i++)
		{
			for(int j = 0; j < this->getHeight() ; j++)
			{
				grid[i][j]->setIsPath(false);
			}
		}

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Agent* agent = this->grid[x][y]->getAgent();
				if (agent != NULL) {
					if (this->grid[x][y]->getState() == StateEnum::minion) {
						minions.push_back(agent);
					}
				}
			}
		}

		size_t size = minions.size();
		for (int i = 0; i < size; i++) {
			minions[i]->action(this);
		}
		/*************/
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Agent* agent = this->grid[x][y]->getAgent();
				if (agent != NULL) {
					if (this->grid[x][y]->getState() == StateEnum::pyroman) {
						pyroman.push_back(agent);
					}
				}
			}
		}

		size = pyroman.size();
		for (int i = 0; i < size; i++) {
			pyroman[i]->action(this);
		}
		/*********/
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Agent* agent = (Minion*)this->grid[x][y]->getAgent();
				if (agent != NULL) {
					if (this->grid[x][y]->getState() == StateEnum::pompier) {
						pompier.push_back(agent);
					}
				}
			}
		}

		size = pompier.size();
		for (int i = 0; i < size; i++) {
			pompier[i]->action(this);
		}



		

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Agent* agent = this->grid[x][y]->getAgent();
				if (agent != NULL) {
					if (this->grid[x][y]->getState() == StateEnum::flame){
						fires.push_back(agent);
					}
				}
			}
		}

		size = fires.size();
		for (int i = 0; i < size; i++) {
			fires[i]->action(this);
		}
	}
