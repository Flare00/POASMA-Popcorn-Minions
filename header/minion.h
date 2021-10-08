#ifndef MINION_H
#define MINION_H

class Minion{
private:
	bool alive = true;
	bool escape = false;
public:
	void move(int x, int y);
	void idle();
	void panik();
	void popcorn();
};

#endif
