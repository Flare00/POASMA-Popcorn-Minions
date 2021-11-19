#ifndef BATIMENT_H
#define BATIMENT_H

#include <vector>
#include "etage.h"

using namespace std;

struct liaisonEntreeSortie
{
	Case* entree;
	Case* sortie;
	liaisonEntreeSortie(Case* entree, Case* sortie) {
		this->entree = entree;
		this->sortie = sortie;
	}
};

class Batiment {
private:
	vector<Etage*> etages;
	vector<liaisonEntreeSortie> liaison;
public:
	Batiment(vector<Etage *> e, vector<liaisonEntreeSortie> l);
	~Batiment();

	vector<Etage*> getEtages();
	vector<liaisonEntreeSortie> getLiaisonEntreesSorties();
	Case* getEntreeLiee(Case* sortie); //Recupere une des sortie liee a une entree 
};

#endif