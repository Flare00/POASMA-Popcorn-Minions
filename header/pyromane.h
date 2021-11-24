#ifndef PYROMANE_H
#define PYROMANE_H
#include "fire.h"
#include "minion.h"

using namespace std;

class Pyromane : public Minion{
	protected:
		bool flagPyroman;
	public:
		Pyromane(int x,int y);
		bool move(Etage* etage, int x, int y);
		virtual void action(Etage* etage);
};
#endif