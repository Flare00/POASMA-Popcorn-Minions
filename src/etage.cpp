#include "etage.h"

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
	return this->cases[x][y];
}

vector<vector<Case*>> Etage::getCases()
{
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
