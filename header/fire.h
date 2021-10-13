#ifndef FIRE_H
#define FIRE_H
#include "agent.h"
#include "case.h"
class Fire : public Agent{
public:
	Fire(int x, int y);
	void propagate( Case * emplacement);
	virtual void action(Batiment* batiment);

};

#endif
