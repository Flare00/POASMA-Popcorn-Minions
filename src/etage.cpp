#include "etage.h"
#include <iostream>
Etage::Etage(int x, int y)
{
	this->cases = vector<vector<Case*>>(x);
	for (int i = 0; i < x; i++) {
		this->cases[i] = vector<Case*>();
		for (int j = 0; j < y; j++) {
			this->cases[i].push_back(new Case(i, j));
		}
	}
}

Etage::Etage(vector<Minion*> minions, vector<Fire*> fires, vector<vector<Case*>> cases, vector<Case*> entrees, vector<Case*> sorties)
{
	this->width = cases.size();
	if (width > 0) {
		this->height = cases[0].size();
	}
	else {
		this->height = 0;
	}
	this->minions = minions;
	this->fires = fires;
	this->cases = cases;
	this->entrees = entrees;
	this->sorties = sorties;
}

Etage::~Etage()
{
	for (int x = 0, maxX = this->cases.size(); x < maxX; x++) {
		for (int y = 0, maxY = this->cases[x].size(); y < maxY; y++) {
			delete this->cases[x][y];
		}
	}
}

Case* Etage::getCase(int x, int y)
{
	if (x >= 0 && y >= 0 && x < this->width && y < this->height) {
		return this->cases[x][y];
	}
	return NULL;
}

vector<vector<Case*>> Etage::getCases()
{
	std::cout << this->cases[0][0] << std::endl;
	return this->cases;
}
vector<vector<Case*>> Etage::getGrid()
{
	return this->cases;
}

vector<Minion*> Etage::getMinions()
{
	return this->minions;
}

vector<Fire*> Etage::getFires()
{
	return this->fires;
}

vector<Case*> Etage::getExitDoors()
{
	return this->sorties;
}

vector<Case*> Etage::getEntryDoors()
{
	return this->entrees;
}

void Etage::addLiaisonEntreeSortie(liaisonEntreeSortie liaison)
{
	this->liaisons.push_back(liaison);
}

int Etage::getWidth()
{
	return this->width;
}

int Etage::getHeight()
{
	return this->height;
}

void Etage::escapeMinion()
{
	//TODO
}

void Etage::burnedMinion()
{
	//TODO
}

int Etage::getRemainingMinions()
{
	return this->minions.size();
}

void Etage::addFire(Case* c, Fire* f)
{
	if (c->getState() == StateEnum::empty || (c->getState() == StateEnum::wall && c->getSubState() == SubStateEnum::wallWood)) {
		c->setState(StateEnum::flame);
		c->setSubState(SubStateEnum::subEmpty);
		c->setAgent((Agent*)f);
		this->fires.push_back(f);
	}
}
bool Etage::removeOneAgent(Agent * agent, bool minion) {
	bool found = false;
	if (minion) {
		vector<Minion*> tmp;
		for (int i = 0, max = this->minions.size(); i < max; i++) {
			if ((Agent*)this->minions[i] != agent) {
				tmp.push_back(this->minions[i]);
				found == true;
			}
		}
		this->minions = tmp;
	}
	else {
		vector<Fire*> tmp;
		for (int i = 0, max = this->fires.size(); i < max; i++) {
			if ((Agent*)this->fires[i] != agent) {
				tmp.push_back(this->fires[i]);
				found == true;
			}
		}
		this->fires = tmp;
	}
	return found;
}
void Etage::kill(Agent* agent, bool minion)
{
	bool found = false;
	if (this->removeOneAgent(agent, minion)) {
		delete agent;
	}
}



Case* Etage::enter(Minion* minion, Case* entree, SubStateEnum substate)
{
	bool found = false;
	int distanceFactor = 1;
	int counter = 0;
	Case* laCase = NULL;
	do {
		counter++;
		int direction = rand() % 3;
		int distance = (rand() % 2 == 0 ? -1 : 1) * distanceFactor;
		if (direction == 0) {
			laCase = this->getCase(entree->getX() + distance, entree->getY());
		}
		else if (direction == 1) {
			laCase = this->getCase(entree->getX(), entree->getY() + distance);
		}
		else {
			int distance2 = (rand() % 2 == 0 ? -1 : 1) * distanceFactor;
			laCase = this->getCase(entree->getX() + distance, entree->getY() + distance2);
		}
		if (laCase != NULL) {
			if (laCase->getState() == empty) {
				laCase->setAgent((Agent*)minion);
				laCase->setState(StateEnum::minion);
				laCase->setSubState(substate);
				found = true;
			}
		}
		if (counter > 12) {
			distanceFactor++;
			counter = 0;
		}
		if (counter > 1000) {
			return NULL;
		}
	} while (!found);
	this->minions.push_back(minion);
	return laCase;
}

Case* Etage::exit(Minion* minion, Case* sortie, SubStateEnum substate)
{
	Case* res = NULL;
	bool found = false;
	for (int i = 0, max = this->liaisons.size(); i < max && !found; i++) {
		if (this->liaisons[i].sortie.porte == sortie) {
			found = true;

			if (this->liaisons[i].exitOnly || this->liaisons[i].entryOnly) {
				this->removeOneAgent((Agent*)minion, true);
			}
			else {
				res = this->liaisons[i].entree.etage->enter(minion, this->liaisons[i].entree.porte, substate);
				this->removeOneAgent((Agent*)minion, true);
			}
		}
	}
	return res;
}


