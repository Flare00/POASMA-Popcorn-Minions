#ifndef ETAGE_H
#define ETAGE_H

#include <vector>
#include "case.h"
class Minion;
class Fire;


using namespace std;
class Etage {
public:
	struct EtagePorte {
		Etage* etage;
		Case* porte;
		EtagePorte() {
			this->etage = NULL;
			this->porte = NULL;
		}
		EtagePorte(Etage* etage, Case* porte) {
			this->etage = etage;
			this->porte = porte;
		}
	};

	struct liaisonEntreeSortie
	{
		EtagePorte entree;
		EtagePorte sortie;
		bool exitOnly = false;
		bool entryOnly = false;
		liaisonEntreeSortie(EtagePorte entree, EtagePorte sortie) {
			this->entree = entree;
			this->sortie = sortie;
		}
		liaisonEntreeSortie(EtagePorte val, bool isEntree) {
			this->entree = val;
			this->sortie = val;
			if (isEntree) {
				this->entryOnly = true;
			}
			else {
				this->exitOnly = true;
			}
		}
	};

private:
	int width, height;
	vector<Minion*> minions;
	vector<Fire*> fires;
	vector<vector<Case*>> cases;
	vector<Case*> sorties;
	vector<Case*> entrees;
	vector<liaisonEntreeSortie> liaisons;
public:
	Etage(int x, int y /*...etc...*/);
	Etage(vector<Minion*> minions, vector<Fire*> fires, vector<vector<Case*>> cases, vector<Case*> entrees, vector<Case*> sorties);
	~Etage();
	Case* getCase(int x, int y);

	vector<vector<Case*>> getCases();
	vector<vector<Case*>> getGrid();
	vector<Minion*> getMinions();
	vector<Fire*> getFires();
	vector<Case*> getExitDoors();
	vector<Case*> getEntryDoors();
	void addLiaisonEntreeSortie(liaisonEntreeSortie liaisons);

	int getWidth();
	int getHeight();
	void escapeMinion();
	void burnedMinion();
	int getRemainingMinions();
	void addFire(Case * c, Fire * f);
	void kill(Agent* Agent, bool minion);
	bool removeOneAgent(Agent* agent, bool minion);
	Case* enter(Minion * minion,Case* entree, SubStateEnum substate);
	Case* exit(Minion* minion, Case* sortie, SubStateEnum substate);

};

#endif