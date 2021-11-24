#ifndef ETAGE_H
#define ETAGE_H

#include <vector>
#include "case.h"
class Minion;
class Fire;

using namespace std;
class Etage {
private:
	int width, height;
	vector<Minion*> minions;
	vector<Fire*> fires;
	vector<vector<Case*>> cases;
	vector<Case*> sorties;
	vector<Case*> entrees;
public:
	Etage(int x, int y /*...etc...*/);
	Etage(vector<Minion*> minions, vector<Fire*> fires, vector<vector<Case*>> cases, vector<Case*> entrees, vector<Case*> sorties);
	~Etage();
	Case* getCase(int x, int y);

	vector<vector<Case*>> getCases();
	vector<vector<Case*>> getGrid();
	vector<Minion*> getMinions();
	vector<Fire*> getFires();
	vector<Case*> getExitDoors();
	vector<Case*> getEntryDoors();
	int getWidth();
	int getHeight();
	void escapeMinion();
	void burnedMinion();
	int getRemainingMinions();
	void addFire(Case * c, Fire * f);
	void kill(Agent* Agent, bool minion);

};

#endif