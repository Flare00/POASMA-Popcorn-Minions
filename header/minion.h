#ifndef MINION_H
#define MINION_H
#include <cstdlib>
#include <ctime>
#include <vector>
#include "agent.h"

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
	~Minion();
	virtual void action(Etage* etage);
	bool move(Etage* etage, int x, int y);
	int calculeHValue(Case * currentCase, Case* goal);
	Case* chooseBestCase(vector<Case *> openList);
	vector<Case *> rebuildPath(Case * c);
	vector<Case *> aStar(Etage* e,Case*  begin, Case* end);
	void printPath(vector<Case *> list);
	int getIndice(vector<Case *> list, Case * c);
	bool checkBoundaries(int x, int y, int width, int height);
	// fonction test a virer
	void printGridAStar(Etage* etage, Case *closestExit, int x, int y);
	void moveToward(Etage* etage, Case * c);
	void idle();
	void panik(Etage* etage);
	void popcorn(Etage* etage);
	
	vector<Case *> children(Etage* b,Case* n);
	void setCaseCurrent(Case * c);
	Case * getCaseCurrent();
	bool isPaniked();
};

#endif
