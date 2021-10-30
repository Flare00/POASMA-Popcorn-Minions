#include <stdlib>
#include <ctime>
#include "batiment.h"

using namespace std;

// CONSTRUCT
Batiment::Batiment(vector<Etage *> e, vector<liaisonEntreeSortie> l)
{
	this->etages = e;
	this->liaison = l;
}

// DESTRUCT
Batiment::~Batiment(){
	for(int i=0, max=this->etages.size() ; i<max ; i++){
		delete this->etages[i];
	}
}

// GETTERS
vector<Etage *> Batiment::getEtages()
{
	return this->etages;
}

vector<liaisonEntreeSortie> Batiment::getLiaisonEntreesSorties()
{
	return this->liaison;
}

Case *Batiment::getEntreeLiee(Case *sortie)
{
	vector<Case *> listEntree;
	for (int i = 0, max = this->liaison.size(); i < max; i++)
	{
		if (this->liaison[i].sortie == sortie)
		{
			listEntree.push_back(this->liaison[i].entree);
		}
	}
	int sizeListEntree = listEntree.size();

	if (sizeListEntree == 0)
	{
		return null;
	}
	else
	{
		srand(clock());
		return listEntree[rand() % sizeListEntree];
	}
}