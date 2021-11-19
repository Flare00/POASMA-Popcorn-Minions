#ifndef AGENT_H
#define AGENT_H

#include "batiment.h"
class Batiment;
class Agent
{
protected:
	int pos_x;
	int pos_y;
public:
	Agent();
	Agent(int x, int y);
	~Agent();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	virtual void action(Etage* etage) =0;
};

#endif
