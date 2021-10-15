#ifndef MINION_H
#define MINION_H

#include <cstdlib>
#include <ctime>

#include "case.h"
#include "agent.h"
#include <vector>
using namespace std;

class Minion : public Agent{
private:
	bool alive = true;
	bool escape = false;
	vector<Case> path;

	Case * current;
	Case * goal;
public:
	Minion(int x, int y);
	virtual void action(Batiment* batiment);
	void move(Batiment* batiment, int deltaX, int deltaY);
	int calculeHValue(Case * currentCase, Case* goal);
	Case* chooseBestCase(vector<Case *> openList);
	vector<Case *> rebuildPath(Case * c);
	vector<Case *> aStar(Batiment* b,Case*  begin, Case* end,Case*** grid);
	void printPath(vector<Case *> list);
	int getIndice(vector<Case *> list, Case * c);
	// fonction test a virer
	void moveToward(Batiment* batiment, Case * c);
	void idle();
	void panik(Batiment* batiment);
	void popcorn();
	
	vector<Case *> children(Batiment* b,Case* n);
	void setCaseCurrent(Case * c);
	Case * getCaseCurrent();
};

#endif
