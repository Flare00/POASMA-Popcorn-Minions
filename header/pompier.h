#ifndef PYROMANE_H
#define PYROMANE_H

#include "case.h"
#include "minion.h"

class Pompier: public Minion{
	protected:
		bool flagPompier;
		int porteeLance = 10;
	public:
		Pompier(int x,int y);
		void eteintFeu(Case* c,Batiment* batiment);
		void move(Batiment* batiment, int x, int y);
		virtual void action(Batiment* batiment);
};
#endif