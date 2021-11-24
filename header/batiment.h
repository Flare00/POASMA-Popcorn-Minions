#ifndef BATIMENT_H
#define BATIMENT_H

#include <vector>
#include "etage.h"

using namespace std;



class Batiment {
private:
	vector<Etage*> etages;
	vector<Etage::liaisonEntreeSortie> liaison;
public:
	Batiment(vector<Etage *> e, vector<Etage::liaisonEntreeSortie> l);
	~Batiment();

	vector<Etage*> getEtages();
	vector<Etage::liaisonEntreeSortie> getLiaisonEntreesSorties();
	Case* getEntreeLiee(Case* sortie); //Recupere une des sortie liee a une entree 
};

#endif