#ifndef MINION_H
#define MINION_H

#include <cstdlib>
#include <ctime>

#include "case.h"
#include "agent.h"

class Minion : public Agent{
private:
	bool alive = true;
	bool escape = false;
public:
	Minion(int x, int y);
	virtual void action(Batiment* batiment);
	void move(Batiment* batiment, int deltaX, int deltaY);

	// fonction test a virer
	void moveToward(Batiment* batiment, Case * c);
	void idle();
	void panik(Batiment* batiment);
	void popcorn();
};

#endif
