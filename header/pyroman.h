#ifndef PYROMAN_H
#define PYROMAN_H
#include "fire.h"
#include "minion.h"

using namespace std;

class Pyroman : public Minion{
	protected:
		bool flagPyroman;
	public:
		Pyroman(int x,int y);
		bool move(Etage* etage, int x, int y);
		virtual void action(Etage* etage);
};
#endif