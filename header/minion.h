#ifndef MINION_H
#define MINION_H

#include <cstdlib>
#include <ctime>
#include "case.h"
#include "agent.h"
#include <vector>
using namespace std;

class Minion : public Agent{
protected:
	bool alive = true;
	bool escape = false;
	bool flagPanik = false;
	short int direction = 0; //0 : Nord, 1 = Est, 2 = Sud, 3 = Ouest
	vector<Case> path;

	Case * current;
	Case * goal;
public:
	//Minion();
	Minion(int x, int y);
	virtual void action(Batiment* batiment);
	bool move(Batiment* batiment, int x, int y);
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
