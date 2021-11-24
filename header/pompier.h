#ifndef POMPIER_H
#define POMPIER_H

#include "minion.h"

class Pompier: public Minion{
	protected:
		bool flagPompier;
		int porteeLance = 10;
	public:
		Pompier(int x,int y);
		void eteintFeu(Case* c, Etage* etage);
		void move(Etage* etage, int x, int y);
		virtual void action(Etage* etage);
};
#endif