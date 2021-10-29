#ifndef PYROMAN_H
#define PYROMAN_H

#include "case.h"
#include "minion.h"

using namespace std;

class Pyroman : public Minion{
	protected:
		bool flagPyroman;
	public:
		Pyroman(int x,int y);
		void move(Batiment* batiment, int x, int y);
		virtual void action(Batiment* batiment);
};
#endif