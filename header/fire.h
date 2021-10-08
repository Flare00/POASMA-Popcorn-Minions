#ifndef FIRE_H
#define FIRE_H
#include "agent.h"
#include "case.h"
class Fire : Agent{
public:
	Fire(int x, int y);
	void propagate( Case * emplacement);
	void action(Batiment* batiment);
};

#endif
