#ifndef AGENT_H
#define AGENT_H

class Agent
{
protected:
	int pos_x;
	int pos_y;
public:

	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

	void action();
};

#endif
