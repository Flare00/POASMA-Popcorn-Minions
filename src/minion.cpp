#include <iostream>
#include <algorithm>
#include "minion.h"

Minion::Minion(int x, int y) {
	this->pos_x = x;
	this->pos_y = y;
}

void Minion::action(Etage* etage) {
	Case* emplacement = etage->getCase(this->getX(), this->getY());
	int x = this->getX();
	int y = this->getY();


	std::vector<Case*> exitDoors = etage->getExitDoors();
	vector<vector<Case*>> grid = etage->getGrid();
	Case* closestExit = exitDoors[0];

	// TODO je sais pas comment connaitre la taille du tableau ? Moi non plus !
	for (int i = 0; i < exitDoors.size(); ++i)
	{
		if (Case::distaceHamilton(exitDoors[i], emplacement) < Case::distaceHamilton(closestExit, emplacement)) {
			closestExit = exitDoors[i];
		}
	}

	vector<Case*> path;
	path.clear();


	path = aStar(etage, emplacement, closestExit);
	/*
	//Debug
	std::cout<<"Départ:"<<x<<" "<<y<<std::endl;
	std::cout<<"Arrivée:"<<closestExit->getX()<<" "<<closestExit->getY()<<std::endl;
	printGridAStar(etage,closestExit,x,y);

	*/
	//printPath(path);

	if (path.size() > 1)
	{

		path.pop_back(); // La case du minion
		Case* to = path.back(); // Le prochain déplacement

		for (int i = 0; i < etage->getWidth(); i++)
			for (int j = 0; j < etage->getHeight(); j++)
			{
				grid[i][j]->setVisited(false);
				grid[i][j]->setParent(NULL);
				grid[i][j]->setF(0);
				grid[i][j]->setG(0);
				grid[i][j]->setH(0);

			}

		if (to->getState() == StateEnum::empty) {
			this->move(etage, to->getX(), to->getY());
		}
	}
	else
	{
		if ((abs(x - closestExit->getX())) <= 1 && (abs(y - closestExit->getY())) <= 1)
		{
			this->move(etage, closestExit->getX(), closestExit->getY());
			etage->escapeMinion();
			//cout<<"Je s'appelle groot"<<endl;
			/*if (etage->getRemainingMinions() == 0)
				exit(0); // On sort quand il trouve la sortie*/
		}
		else {
			this->panik(etage);
		}
	}



}
void Minion::printGridAStar(Etage* etage, Case* closestExit, int x, int y)
{
	vector<vector<Case*>> grid = etage->getGrid();
	for (int i = 0; i < etage->getHeight(); i++)
	{
		for (int j = 0; j < etage->getWidth(); j++)
		{

			if ((etage->getHeight() - 1 - i) == y && j == x)
				std::cout << "X" << " ";
			else if ((etage->getHeight() - 1 - i) == closestExit->getY() && j == closestExit->getX())
				std::cout << "[]" << " ";
			else
				std::cout << grid[etage->getHeight() - 1 - i][j]->getH() << " ";
		}
		std::cout << " " << std::endl;
	}

}
void Minion::setCaseCurrent(Case* c)
{
	this->current = c;
}
Case* Minion::getCaseCurrent()
{
	return this->current;
}
bool Minion::isPaniked()
{
	return this->flagPanik;
}
int Minion::calculeHValue(Case* currentCase, Case* goal)
{
	return max(abs(currentCase->getX() - goal->getX()) + abs(currentCase->getY() - goal->getY()), 0);
}
Case* Minion::chooseBestCase(vector<Case*> openList)
{


	Case* best = openList.front();
	for (size_t i = 0; i < openList.size(); i++)
	{
		if (best->getF() > openList[i]->getF())
		{
			best = openList[i];
		}
	}
	return best;
}
vector<Case*> Minion::rebuildPath(Case* c)
{
	vector<Case*> p;

	int count = 0;
	while (c->getParent() != NULL & count < 10000)
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
int Minion::getIndice(vector<Case*> list, Case* c)
{
	int result = -1;
	for (int i = 0; i < list.size(); i++)
	{
		if (c == list[i])
			result = i;
	}
	return result;
}
void Minion::printPath(vector<Case*> list)
{
	if (list.size() > 0)
	{
		//for(int i = 0 ; i < list.size(); i++)
		//	std::cout<<list[i]->getX()<<" "<<list[i]->getY()<<std::endl;

	}

}
bool Minion::checkBoundaries(int x, int y, int width, int height)
{
	return x >= 0 && x < width&& y >= 0 && y < height;
}


vector<Case*>  Minion::children(Etage* e, Case* n) {
	vector<Case*>  voisinNonVerfier;
	int x = n->getX();
	int y = n->getY();

	int width = e->getWidth();
	int height = e->getHeight();


	if (checkBoundaries(x + 1, y, width, height))
	{
		if (e->getCase(x + 1, y)->getState() == empty || e->getCase(x + 1, y)->getState() == exitDoor || e->getCase(x + 1, y)->getState() == minion)
		{
			voisinNonVerfier.push_back(e->getCase(n->getX() + 1, n->getY()));
		}
	}
	if (checkBoundaries(x - 1, y, width, height))
	{
		if (e->getCase(x - 1, y)->getState() == empty || e->getCase(x - 1, y)->getState() == exitDoor || e->getCase(x - 1, y)->getState() == minion)
		{
			voisinNonVerfier.push_back(e->getCase(n->getX() - 1, n->getY()));
		}
	}

	if (checkBoundaries(x, y + 1, width, height))
	{
		if (e->getCase(x, y + 1)->getState() == empty || e->getCase(x, y + 1)->getState() == exitDoor || e->getCase(x, y + 1)->getState() == minion)
		{
			voisinNonVerfier.push_back(e->getCase(n->getX(), n->getY() + 1));
		}
	}
	if (checkBoundaries(x, y - 1, width, height))
	{
		if (e->getCase(x, y - 1)->getState() == empty || e->getCase(x, y - 1)->getState() == exitDoor || e->getCase(x, y - 1)->getState() == minion)
		{
			voisinNonVerfier.push_back(e->getCase(n->getX(), n->getY() - 1));
		}
	}

	return voisinNonVerfier;
}
vector<Case*> Minion::aStar(Etage* e, Case* begin, Case* end)
{
	vector<Case*> openList;
	vector<Case*> closedList;
	//openList.clear();
	//closedList.clear();

	openList.push_back(begin);
	begin->setG(0);
	begin->setH(calculeHValue(begin, end));
	begin->setH(begin->getH());
	int indice;

	while (!openList.empty())
	{
		/*for(int i = 0 ; i < openList.size() ; i++)
		{
			std::cout<<openList[i]->getX()<<":"<<openList[i]->getY()<<" "<<endl;;
		}*/
		Case* n = chooseBestCase(openList);
		if (end->getX() == n->getX() && end->getY() == n->getY())
			return rebuildPath(n);
		indice = getIndice(openList, n);
		vector<Case*>::iterator nth = openList.begin() + indice;
		if (indice != -1) // On efface n 
			openList.erase(nth);
		closedList.push_back(n);
		n->setVisited(true);

		vector<Case*> child = children(e, n);
		for (int i = 0; i < child.size(); i++) {
			if (std::find(closedList.begin(), closedList.end(), child[i]) != closedList.end()) // child[i] in closedlist ?
				continue;

			int cost;
			if (child[i]->getState() == minion) {
				cost = 1;
			}
			else {
				cost = 1;
			}
			bool bestCost = false;
			if (!(std::find(openList.begin(), openList.end(), child[i]) != openList.end())) { // child[i] not in openlist ?
				openList.push_back(child[i]);

				child[i]->setH(calculeHValue(child[i], end));

				bestCost = true;
			}
			else if (cost < child[i]->getG())
				bestCost = true;
			if (bestCost) {
				child[i]->setParent(n);
				child[i]->setG(cost);
				child[i]->setF(child[i]->getG() + child[i]->getH());

			}

		}



	}

	return {};


}
bool Minion::move(Etage* etage, int x, int y) {
	bool moved = false;
	Case* emplacement = etage->getCase(x, y);
	if (emplacement != NULL) {
		Case* currentCase = etage->getCase(this->getX(), this->getY());
		switch (emplacement->getState()) {
		case StateEnum::empty:
			moved = true;
			emplacement->setState(StateEnum::minion);
			emplacement->setAgent(this);
			this->setX(x);
			this->setY(y);
			currentCase->setState(StateEnum::empty);
			currentCase->setAgent(NULL);
			break;
		case StateEnum::flame:
			moved = true;
			emplacement->setState(StateEnum::popCorn);
			delete emplacement->getAgent();
			currentCase->setState(StateEnum::empty);
			currentCase->setAgent(NULL);
			delete this;
			break;
		case StateEnum::exitDoor:
			moved = true;
			currentCase->setState(StateEnum::empty);
			currentCase->setAgent(NULL);
			delete this;
			break;
		}
	}
	return moved;
}
void Minion::idle() {

}
void Minion::panik(Etage* etage) {
	//	srand(clock());
	this->flagPanik = true;
	int deplacement = (rand() % 2 == 0) ? -1 : 1;
	int direction = (rand() % 2);

	if (direction == 0) {
		this->move(etage, this->getX() + deplacement, this->getY());
	}
	else {
		this->move(etage, this->getX(), this->getY() + deplacement);
	}

}
void Minion::popcorn() {
	delete this;
}

void Minion::moveToward(Etage* etage, Case* c) {
	int dx = 0;
	int dy = 0;

	if (c->getX() > this->getX()) {
		dx = 1;
	}
	else if (c->getX() < this->getX()) {
		dx = -1;
	}

	if (c->getY() > this->getY()) {
		dy = 1;
	}
	else if (c->getY() < this->getY()) {
		dy = -1;
	}
	this->move(etage, dx, dy);
}