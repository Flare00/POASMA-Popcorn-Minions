#ifndef FIRE_H
#define FIRE_H

#include "agent.h"
#include "minion.h"
class Fire : public Agent{
private:
	bool pauseUnTour = false;
public:
	Fire(int x, int y);
	void propagate( Case * emplacement, Etage* etage);
	void pause();
	virtual void action(Etage* etage);

};

#endif
