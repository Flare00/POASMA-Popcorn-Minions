#ifndef ETAGE_H
#define ETAGE_H

#include "minion.h"
#include "fire.h"
#include "case.h"

class Etage{
	private :
		vector<Minions*> minions;
		vector<Fire*> fires;
		vector<vector<Case*>> cases;
	public :
		Etage(int x, int y /*...etc...*/);
		Etage(vector<vector<Case*>> cases);		
		~Etage();
		Case * getCase(int x, int y);
		
		vector<vector<Case*>> getCases();
		vector<Minions*> getMinions();
		vector<Fire*> getFires();
}

#endif