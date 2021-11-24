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
	if(c->getState() == StateEnum::empty || (c->getState() == StateEnum::wall && c->getSubState() == SubStateEnum::wallWood)){
		c->setState(StateEnum::flame);
		c->setSubState(SubStateEnum::subEmpty);
		c->setAgent((Agent*)f);
		this->fires.push_back(f);
	}
}

void Etage::kill(Agent* agent, bool minion)
{
	bool found = false;
	if (minion) {
		for (int i = 0, max = this->minions.size(); i < max && !found; i++) {
			if ((Agent*)this->minions[i] == agent) {
				this->minions.erase(this->minions.begin() + i);
			}
		}
	}
	else {
		for (int i = 0, max = this->fires.size(); i < max && !found; i++) {
			if ((Agent*)this->fires[i] == agent) {
				this->fires.erase(this->fires.begin() + i);
			}
		}
	}
	if (found) {
		delete agent;
	}
}
