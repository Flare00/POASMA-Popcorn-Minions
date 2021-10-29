#ifndef FIRE_H
#define FIRE_H
#include "agent.h"
#include "case.h"
class Fire : public Agent{
private:
	bool pauseUnTour = false;
public:
	Fire(int x, int y);
	void propagate( Case * emplacement,Batiment * batiment);
	void pause();
	virtual void action(Batiment* batiment);

};

#endif
