#ifndef BATIMENT_H
#define BATIMENT_H

#include "case.h"
#include "stateEnum.h"

class Batiment
{
private:
	int width;
	int height;
	int start_nbminion, start_nbfire;
	int nb_exits;
	Case*** grid;

public:
	Batiment(int x, int y, int start_nbminion, int start_nbfire, int nb_exits ,int nb_wall);
	~Batiment();

	Case** getExitDoors(); //Return all exit cases;

	StateEnum getState(int x, int y);
	Case* getCase(int x, int y);
	Case*** getGrid();
	int getWidth();
	int getHeight();
	void doAction();
};

#endif
