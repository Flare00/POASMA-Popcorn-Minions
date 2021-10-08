#ifndef BATIMENT_H
#define BATIMENT_H

#include "case.h"

class Batiment
{
private:
	int width;
	int height;

	Case** grid;

public:
	Batiment(int x, int y);
	~Batiment();

	bool fire(int x, int y);    //is there fire in (x,y)
	int* getExitDoors(); //fill the tab "tab" and set n to the number of exit


	bool flamable(int x, int y);
	Case* getCase(int x, int y);
	Case** getGrid();

};

#endif
