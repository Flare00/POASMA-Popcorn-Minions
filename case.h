#include "agent.h"

enum StateEnum{
	free,
	wall,
	flame,
	minion,
	exit
}

class Case{
private : 
	StateEnum state;
	Agent agent;
public :
	StateEnum getState();
	void setState(StateEnum state);
	Agent getAgent();
	void setAgent(Agent agent)
}

