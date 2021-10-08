#ifndef CASE_H
#define CASE_H

#include "agent.h"
#include "stateEnum.h"

class Case{
private : 
	StateEnum state;
	Agent agent;
public :
	StateEnum getState();
	void setState(StateEnum state);
	Agent getAgent();
	void setAgent(Agent agent);
};

#endif
