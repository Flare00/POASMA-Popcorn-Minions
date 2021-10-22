#include "minion.h"
#include "case.h"
#include "batiment.h"
#include <iostream>
#include <algorithm>

Minion::Minion(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}

void Minion::action(Batiment* batiment){
	Case* emplacement = batiment->getCase(this->getX(), this->getY());
	int x = this->getX();
	int y = this->getY();


		std::vector<Case *> exitDoors = batiment->getExitDoors();
		Case*** grid = batiment->getGrid();
		Case* closestExit = exitDoors[0];

		// TODO je sais pas comment connaitre la taille du tableau ? Moi non plus !
		for (int i = 0; i < exitDoors.size(); ++i) 
		{
			if(Case::distaceHamilton(exitDoors[i],emplacement)<Case::distaceHamilton(closestExit,emplacement)){
				closestExit = exitDoors[i];
			}
		}

		vector<Case *> path;
		path.clear();


		path = aStar(batiment,emplacement,closestExit);
		/*
		//Debug
		std::cout<<"Départ:"<<x<<" "<<y<<std::endl;
		std::cout<<"Arrivée:"<<closestExit->getX()<<" "<<closestExit->getY()<<std::endl;
		printGridAStar(batiment,closestExit,x,y);
		
		*/
		//printPath(path);

		if(path.size()>1)
		{

			path.pop_back(); // La case du minion
			Case * to = path.back(); // Le prochain déplacement

			for(int i = 0; i < batiment->getWidth() ; i++)
				for(int j = 0; j < batiment->getHeight() ; j++)
				{
					grid[i][j]->setVisited(false);
					grid[i][j]->setParent(NULL);
					grid[i][j]->setF(0);
					grid[i][j]->setG(0);
					grid[i][j]->setH(0);

				}

			if(to->getState() == StateEnum::empty){
				this->move(batiment, to->getX(),to->getY());
			}
		}
		else
		{	
			if( (abs(x-closestExit->getX())) <=1 && (abs(y-closestExit->getY()))<=1 )
			{
				this->move(batiment, closestExit->getX(),closestExit->getY());
				batiment->escapeMinion();
				//cout<<"Je s'appelle groot"<<endl;
				/*if (batiment->getRemainingMinions() == 0)
					exit(0); // On sort quand il trouve la sortie*/
			}
			else {
				this->panik(batiment);
			}
		}
		
		
	
}
void Minion::printGridAStar(Batiment* batiment, Case *closestExit, int x, int y)
{
	Case*** grid = batiment->getGrid();
		for(int i = 0; i < batiment->getHeight() ; i++)
		{
			for(int j = 0; j < batiment->getWidth() ; j++)
				{
					
					if( (batiment->getHeight()-1-i) == y && j == x)
						std::cout<<"X"<<" ";
					else if( (batiment->getHeight()-1-i) == closestExit->getY() && j == closestExit->getX())
						std::cout<<"[]"<<" ";
					else
						std::cout<<grid[batiment->getHeight()-1-i][j]->getH()<<" ";
				}
				std::cout<<" "<<std::endl;
		}

}
void Minion::setCaseCurrent(Case * c)
{
	this->current = c;
}
Case * Minion::getCaseCurrent()
{
	return this->current;
}
bool Minion::isPaniked()
{
	return this->flagPanik;
}
int Minion::calculeHValue(Case * currentCase, Case* goal)
{
	return max(abs(currentCase->getX() - goal->getX())+abs(currentCase->getY() - goal->getY()),0);
}
Case* Minion::chooseBestCase(vector<Case *> openList)
{


	Case * best = openList.front();
	for(size_t i = 0 ; i < openList.size() ; i++)
	{
		if( best->getF() > openList[i]->getF() )
		{
			best = openList[i];
		}
	}
	return best;
}
vector<Case *> Minion::rebuildPath(Case * c)
{
	vector<Case *> p;

	int count = 0;
	while(c->getParent() != NULL & count<10000)
	{
		count++;
		c = c->getParent();
		//c->setVisited(true);
		c->setIsPath(true);
		p.push_back(c);
		
	}
	//cout<<count<<endl;
	return p;
}
int Minion::getIndice(vector<Case *> list, Case * c)
{
	int result = -1;
	for(int i = 0 ; i < list.size(); i++)
	{
		if(c==list[i])
			result= i;
	}
	return result;
}
void Minion::printPath(vector<Case *> list)
{
	if(list.size()>0)
	{
		//for(int i = 0 ; i < list.size(); i++)
		//	std::cout<<list[i]->getX()<<" "<<list[i]->getY()<<std::endl;

	}

}
bool Minion::checkBoundaries(int x, int y, int width, int height)
{
	return x>=0&&x<width && y>=0&&y<height;
}
vector<Case *>  Minion::children(Batiment* b,Case* n){
	vector<Case *>  voisinNonVerfier;
	int x = n->getX();
	int y = n->getY();

	int width = b->getWidth();
	int height = b->getHeight();


	if ( checkBoundaries(x+1,y,width,height) )
	{
		if(b->getCase(x+1,y)->getState()==empty||b->getCase(x+1,y)->getState()==exitDoor||b->getCase(x+1,y)->getState()==minion)
		{
			voisinNonVerfier.push_back(b->getCase(n->getX()+1,n->getY()));
		}
	}
	if ( checkBoundaries(x-1,y,width,height))
	{
		if(b->getCase(x-1,y)->getState()==empty||b->getCase(x-1,y)->getState()==exitDoor||b->getCase(x-1,y)->getState()==minion)
		{
			voisinNonVerfier.push_back(b->getCase(n->getX()-1,n->getY()));
		}
	}

	if ( checkBoundaries(x,y+1,width,height))
	{
		if(b->getCase(x,y+1)->getState()==empty||b->getCase(x,y+1)->getState()==exitDoor||b->getCase(x,y+1)->getState()==minion)
		{
			voisinNonVerfier.push_back(b->getCase(n->getX(),n->getY()+1));
		}
	}
	if ( checkBoundaries(x,y-1,width,height))
	{
		if(b->getCase(x,y-1)->getState()==empty||b->getCase(x,y-1)->getState()==exitDoor||b->getCase(x,y-1)->getState()==minion)
		{
			voisinNonVerfier.push_back(b->getCase(n->getX(),n->getY()-1));
		}
	}

	return voisinNonVerfier;
}
vector<Case *> Minion::aStar(Batiment* b,Case*  begin, Case* end)
{
	 vector<Case *> openList;
	 vector<Case *> closedList;
	 //openList.clear();
	 //closedList.clear();

	 openList.push_back(begin);
	 begin->setG(0);
	 begin->setH(calculeHValue(begin,end));
	 begin->setH(begin->getH());
	 int indice;

	 while(!openList.empty())
	 {
	 	/*for(int i = 0 ; i < openList.size() ; i++)
	 	{
	 		std::cout<<openList[i]->getX()<<":"<<openList[i]->getY()<<" "<<endl;;
	 	}*/
	 	Case* n = chooseBestCase(openList);
	 	if( end->getX()==n->getX() && end->getY()==n->getY())
	 		return rebuildPath(n);
	 	indice = getIndice(openList, n);
	 	vector<Case*>::iterator nth = openList.begin() + indice;
	 	if(indice!=-1) // On efface n 
	 		openList.erase(nth);
	 	closedList.push_back(n);
	 	n->setVisited(true);

	 	vector<Case *> child=children(b,n);
	 	for(int i=0;i<child.size();i++){
	 		if(std::find(closedList.begin(),closedList.end(),child[i])!=closedList.end()) // child[i] in closedlist ?
	 			continue;

	 		int cost;
	 		if(child[i]->getState()==minion){
	 			cost = 1;
	 		}else{
	 			cost = 1;
	 		}
	 		bool bestCost=false;
	 		if(!(std::find(openList.begin(),openList.end(),child[i])!=openList.end())){ // child[i] not in openlist ?
	 			openList.push_back(child[i]);
	 			
	 			child[i]->setH(calculeHValue(child[i],end));

	 			bestCost=true;
	 		}else if(cost < child[i]->getG())
	 				bestCost=true;
	 		if(bestCost){
	 			child[i]->setParent(n);
	 			child[i]->setG(cost);
	 			child[i]->setF(child[i]->getG()+child[i]->getH());

	 		}

	 	}
	 


	 }

	 return {};


}
void Minion::move(Batiment* batiment, int x, int y){
	Case* emplacement = batiment->getCase(x,y);
	if (emplacement != NULL) {
		Case* currentCase = batiment->getCase(this->getX(), this->getY());
		switch (emplacement->getState()) {
			case StateEnum::empty :
				emplacement->setState(StateEnum::minion);
				emplacement->setAgent(this);
				this->setX(x);
				this->setY(y);
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
//	srand(clock());
	this->flagPanik = true;
	int deplacement = (rand() % 2 == 0) ? -1 : 1;
	int direction = (rand() % 2);

	if (direction == 0) {
		this->move(batiment, this->getX() + deplacement, this->getY());	
	}
	else {
		this->move(batiment, this->getX(), this->getY() + deplacement);	
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