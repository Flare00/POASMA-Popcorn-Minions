#ifndef CASE_H
#define CASE_H

#include "stateEnum.h"
#include "agent.h"
class Case{
private : 
	StateEnum state;
	Agent * agent;
	int pos_x, pos_y;
	int f,g,h;
	Case * parent;
	bool visited;
	bool isPath;
public :
	Case(int x, int y);
	~Case();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

	void setF(int f);
	void setG(int g);
	void setH(int h);
	
	StateEnum getState();
	void setState(StateEnum state);
	Agent* getAgent();
	void setAgent(Agent* agent);

	void setParent(Case* parent);
	Case* getParent();

	int getF();
	int getG();
	int getH();

	bool getVisited();
	void setVisited(bool visited);

	bool getIsPath();
	void setIsPath(bool isPath);
	
	static int distaceHamilton(Case* c1,Case* c2);
};

#endif
