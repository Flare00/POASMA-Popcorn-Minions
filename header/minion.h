#ifndef MINION_H
#define MINION_H

#include <cstdlib>
#include <ctime>
#include "Mind.hpp"
#include "case.h"
#include "agent.h"
#include <vector>
using namespace std;

class Minion : public Agent{
private:
	bool alive = true;
	bool escape = false;
	bool flagPanik = false;
	vector<Case> path;

	Case * current;
	Case * goal;
	Mind* mind;
public:
	Minion(int x, int y, int seed);
	virtual void action(Batiment* batiment);
	void move(Batiment* batiment, int x, int y);
	int calculeHValue(Case * currentCase, Case* goal);
	Case* chooseBestCase(vector<Case *> openList);
	vector<Case *> rebuildPath(Case * c);
	vector<Case *> aStar(Batiment* b,Case*  begin, Case* end);
	void printPath(vector<Case *> list);
	int getIndice(vector<Case *> list, Case * c);
	bool checkBoundaries(int x, int y, int width, int height);
	// fonction test a virer
	void printGridAStar(Batiment* batiment, Case *closestExit, int x, int y);
	void moveToward(Batiment* batiment, Case * c);
	void idle();
	void panik(Batiment* batiment);
	void popcorn();
	
	vector<Case *> children(Batiment* b,Case* n);
	void setCaseCurrent(Case * c);
	Case * getCaseCurrent();
	bool isPaniked();
};

#endif
