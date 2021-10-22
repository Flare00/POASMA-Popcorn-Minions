#ifndef BATIMENT_H
#define BATIMENT_H

#include <vector>
#include "case.h"
#include "stateEnum.h"

class Batiment
{
private:
	int width;
	int height;
	int start_nbminion, start_nbfire;
	int nb_exits;
	int escapedMinion;
	Case*** grid;

public:
	Batiment(int x, int y, int start_nbminion, int start_nbfire, int nb_exits ,int nb_wall);
	~Batiment();

	std::vector<Case *> getExitDoors(); //Return all exit cases;

	StateEnum getState(int x, int y);

	Case* getCase(int x, int y);
	Case*** getGrid();
	int getWidth();
	int getHeight();

	void escapeMinion();
	void burnedMinion();
	int getRemainingMinions();
	void doAction();

	
};

#endif
