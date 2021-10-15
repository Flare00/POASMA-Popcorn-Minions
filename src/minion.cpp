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
	vector<Case *> path;
	current->setX(x);
	current->setY(y);
	path = aStar(batiment,this->current,this->current,batiment->getGrid());
	printPath(path);
}
void Minion::setCaseCurrent(Case * c)
{
	this->current = c;
}
Case * Minion::getCaseCurrent()
{
	return this->current;
}
int Minion::calculeHValue(Case * currentCase, Case* goal)
{
	return abs(currentCase->getX() - goal->getX())+abs(currentCase->getY() - goal->getY());
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
	if(c->getParent() != NULL)
	{
		vector<Case *> p = rebuildPath(c->getParent());
		c->setVisited(true);
		p.push_back(c);
		return p;
	}
	else
		return {};


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
	for(int i = 0 ; i < list.size(); i++)
		std::cout<<list[i]->getX()<<" "<<list[i]->getY()<<std::endl;
}
vector<Case *>  Minion::children(Batiment* b,Case* n){
	vector<Case *>  voisinNonVerfier;
	if(b->getCase(n->getX(),n->getY()+1)->getState()==empty) voisinNonVerfier.push_back(b->getCase(n->getX(),n->getY()+1));
	if(b->getCase(n->getX()+1,n->getY())->getState()==empty) voisinNonVerfier.push_back(b->getCase(n->getX()+1,n->getY()));
	if(b->getCase(n->getX(),n->getY()-1)->getState()==empty) voisinNonVerfier.push_back(b->getCase(n->getX(),n->getY()-1));
	if(b->getCase(n->getX()-1,n->getY())->getState()==empty) voisinNonVerfier.push_back(b->getCase(n->getX()-1,n->getY()));
	return voisinNonVerfier;
}
vector<Case *> Minion::aStar(Batiment* b,Case*  begin, Case* end,Case*** grid)
{
	 vector<Case *> openList;
	 vector<Case *> closedList;

	 openList.push_back(begin);
	 begin->setG(0);
	 begin->setH(calculeHValue(begin,end));
	 begin->setH(begin->getH());
	 int indice;

	 while(!openList.empty())
	 {
	 	Case* n = chooseBestCase(openList);
	 	if( end->getX()==n->getX() && end->getY()==n->getY())
	 		return rebuildPath(n);
	 	indice = getIndice(openList, n);
	 	vector<Case*>::iterator nth = openList.begin() + indice;
	 	if(indice!=-1) // On efface n 
	 		openList.erase(nth);
	 	closedList.push_back(n);

	 	vector<Case *> child=children(b,n);
	 	for(int i=0;i<child.size();i++){
	 		if(std::find(closedList.begin(),closedList.end(),child[i])!=closedList.end())
	 			continue;

	 		int cost=1;
	 		bool bestCost=false;
	 		if(!(std::find(openList.begin(),openList.end(),child[i])!=openList.end())){
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