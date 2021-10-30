#ifndef BATIMENT_H
#define BATIMENT_H

#include <vector>
#include "etage.h"

using namespace std;
struct liaisonEntreeSortie
{
	Case* entree;
	Case* sortie;
};
class Batiment {
private:
	vector<Etage*> etages;
	vector<liaisonEntreeSortie> liaison;
public:
	Batiment(vector<Etage> etages);
	~Batiment();

	vector<Etage*> getEtages();
	vector<liaisonEntreeSortie> getLiaisonEntreesSorties();
	Case* getSortieLiee(Case* entree); //Recupere une des sortie liee a une entree 
}

#endif