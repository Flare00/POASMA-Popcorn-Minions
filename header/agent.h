#ifndef AGENT_H
#define AGENT_H

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

	
	virtual void action(Batiment* batiment) = 0;
};

#endif
