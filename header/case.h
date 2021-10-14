#ifndef CASE_H
#define CASE_H

#include "stateEnum.h"
#include "agent.h"
class Case{
private : 
	StateEnum state;
	Agent * agent;
	int pos_x, pos_y;
public :
	Case(int x, int y);
	~Case();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	
	StateEnum getState();
	void setState(StateEnum state);
	Agent* getAgent();
	void setAgent(Agent* agent);

	static int distaceHamilton(Case* c1,Case* c2);
};

#endif
