#ifndef MINION_H
#define MINION_H

#include "agent.h"
class Minion : public Agent{
private:
	bool alive = true;
	bool escape = false;
public:
	Minion(int x, int y);
	virtual void action(Batiment* batiment);
	void move(Batiment* batiment, int deltaX, int deltaY);
	void idle();
	void panik(Batiment* batiment);
	void popcorn();
};

#endif
