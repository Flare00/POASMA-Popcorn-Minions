#include <iostream>
#include "Simulation.h"
using namespace std;
Simulation::Simulation()
{
	//this->batiment = Simulation::generateBatiment(1, 10, 10, NBbMinionsParam(0, 5, 0), 0, 1, 1, 1, 1);
	this->batiment = Simulation::generateBatiment(3, 10, 10, NBbMinionsParam(1, 0, 0), 0, 1, 1, 0, 0);

}

Simulation::~Simulation() {
	vector<Etage*> etages = this->batiment->getEtages();
	for (int i = 0, max = etages.size(); i < max; i++) {
		vector<Minion*> minions = etages[i]->getMinions();
		vector<Fire*> fires = etages[i]->getFires();
		for (int j = 0, maxJ = minions.size(); j < maxJ; j++) {
			delete minions[j];
		}
		for (int j = 0, maxJ = fires.size(); j < maxJ; j++) {
			delete fires[j];
		}
	}
	delete batiment;
}

Batiment* Simulation::generateBatiment(int nbEtages, int largeur, int hauteur, NBbMinionsParam nbMinions, int start_nbfire, int nb_exits, int nb_enters, int nb_wall, int nb_wood_wall)
{
	srand(clock());
	vector<Etage*> etages;
	vector<Etage::liaisonEntreeSortie> link;
	vector<vector<Etage::EtagePorte>> allEntree;
	vector<vector<Etage::EtagePorte>> allSortie;

	for (int i = 0; i < nbEtages; i++) {
		vector<vector<Case*>> cases;
		vector<Minion*> minions;
		vector<Fire*> fires;
		vector<Case*> sorties;
		vector<Case*> entrees;
		int nbStdMinions = (nbMinions.maxStandardEtage == nbMinions.minStandardEtage) ? nbMinions.maxStandardEtage : (rand()% (nbMinions.maxStandardEtage - nbMinions.minStandardEtage)) + nbMinions.minStandardEtage;
		int nbPompMinions = (nbMinions.maxPompierEtage == nbMinions.minPompierEtage) ? nbMinions.maxPompierEtage : (rand() % (nbMinions.maxPompierEtage - nbMinions.minPompierEtage)) + nbMinions.minPompierEtage;
		int nbPyroMinions = (nbMinions.maxPyromaneEtage == nbMinions.minPyromaneEtage) ? nbMinions.maxPyromaneEtage : (rand() % (nbMinions.maxPyromaneEtage - nbMinions.minPyromaneEtage)) + nbMinions.minPyromaneEtage;
		int counterStd = 0, counterPomp = 0, counterPyro = 0, counterFires = 0, counterEnter = 0, counterExits = 0, counterWalls = 0, counterWoodWalls = 0;
		for (int x = 0; x < largeur; x++) {
			vector<Case*> colonne;
			for (int y = 0; y < hauteur; y++) {
				Case* cellule = new Case(x, y);
				colonne.push_back(cellule);
			}
			cases.push_back(colonne);
		}

		while (counterStd < nbStdMinions || counterPomp < nbPompMinions || counterPyro < nbPyroMinions || counterFires < start_nbfire || counterEnter < nb_enters || counterExits < nb_exits || counterWalls < nb_wall || counterWoodWalls < nb_wood_wall) {
			if (counterStd < nbStdMinions) {
				int x = rand() % largeur, y = rand() % hauteur;
				if (cases[x][y]->getState() == StateEnum::empty) {
					Minion* m = new Minion(x, y);
					cases[x][y]->setState(StateEnum::minion);
					cases[x][y]->setSubState(SubStateEnum::subEmpty);
					cases[x][y]->setAgent(m);
					minions.push_back(m);
					counterStd++;
				}
			}
			if (counterPomp < nbPompMinions) {
				int x = rand() % largeur, y = rand() % hauteur;
				if (cases[x][y]->getState() == StateEnum::empty) {
					Pompier* m = new Pompier(x, y);
					cases[x][y]->setState(StateEnum::minion);
					cases[x][y]->setSubState(SubStateEnum::pompier);
					cases[x][y]->setAgent(m);
					minions.push_back(m);
					counterPomp++;
				}
			}
			if (counterPyro < nbPyroMinions) {
				int x = rand() % largeur, y = rand() % hauteur;
				if (cases[x][y]->getState() == StateEnum::empty) {
					Pyroman* m = new Pyroman(x, y);
					cases[x][y]->setState(StateEnum::minion);
					cases[x][y]->setSubState(SubStateEnum::pyroman);
					cases[x][y]->setAgent(m);
					minions.push_back(m);
					counterPyro++;
				}
			}
			if (counterFires < start_nbfire) {
				int x = rand() % largeur, y = rand() % hauteur;
				if (cases[x][y]->getState() == StateEnum::empty) {
					Fire* f = new Fire(x, y);
					cases[x][y]->setState(StateEnum::flame);
					cases[x][y]->setSubState(SubStateEnum::subEmpty);
					cases[x][y]->setAgent(f);
					fires.push_back(f);
					counterFires++;
				}
			}
			if (counterExits < nb_exits) {
				int x = rand() % largeur, y = rand() % hauteur;
				if (cases[x][y]->getState() == StateEnum::empty) {
					cases[x][y]->setState(StateEnum::exitDoor);
					cases[x][y]->setSubState(SubStateEnum::subEmpty);
					sorties.push_back(cases[x][y]);
					counterExits++;
				}
			}
			if (counterEnter < nb_enters) {
				int x = rand() % largeur, y = rand() % hauteur;
				if (cases[x][y]->getState() == StateEnum::empty) {
					cases[x][y]->setState(StateEnum::enterDoor);
					cases[x][y]->setSubState(SubStateEnum::subEmpty);
					entrees.push_back(cases[x][y]);
					counterEnter++;
				}
			}
			if (counterWalls < nb_wall) {
				int x = rand() % largeur, y = rand() % hauteur;
				if (cases[x][y]->getState() == StateEnum::empty) {
					cases[x][y]->setState(StateEnum::wall);
					cases[x][y]->setSubState(SubStateEnum::subEmpty);
					counterWalls++;
				}
			}
			if (counterWoodWalls < nb_wood_wall) {
				int x = rand() % largeur, y = rand() % hauteur;
				if (cases[x][y]->getState() == StateEnum::empty) {
					cases[x][y]->setState(StateEnum::wall);
					cases[x][y]->setSubState(SubStateEnum::wallWood);
					counterWoodWalls++;
				}
			}

		}
		Etage* etage = new Etage(minions, fires, cases, entrees, sorties);
		etages.push_back(etage);
		vector<Etage::EtagePorte> etagesEntree;
		vector<Etage::EtagePorte> etagesSortie;

		for (int j = 0, maxJ = entrees.size(); j < maxJ; j++) {
			etagesEntree.push_back(Etage::EtagePorte(etage, entrees[j]));
		}
		for (int j = 0, maxJ = sorties.size(); j < maxJ; j++) {
			etagesSortie.push_back(Etage::EtagePorte(etage, sorties[j]));
		}
		allEntree.push_back(etagesEntree);
		allSortie.push_back(etagesSortie);

	}

	for (int i = nbEtages - 1; i >= 0; i--) {
		if (i == nbEtages - 1) {
			for (int j = 0, max = allEntree[i].size(); j < max; j++) {
				Etage::liaisonEntreeSortie l(allEntree[i][j], true);
				link.push_back(l);
				l.sortie.etage->addLiaisonEntreeSortie(l);
			}
		}

		if (i == 0) {
			for (int j = 0, max = allSortie[i].size(); j < max; j++) {
				Etage::liaisonEntreeSortie l( allSortie[i][j], false);
				link.push_back(l);
			}
		}
		else
		{
			for (int j = 0, max = allSortie[i].size(); j < max; j++) {
				for (int k = 0, maxk = allEntree[i - 1].size(); k < maxk; k++) {
					Etage::liaisonEntreeSortie l(allEntree[i - 1][k], allSortie[i][j]);
					link.push_back(l);
					l.sortie.etage->addLiaisonEntreeSortie(l);
				}
			}
		}
	}
	return new Batiment(etages, link);
}

Batiment* Simulation::generateBatiment(vector<Etage*> etages, vector<Etage::liaisonEntreeSortie> liaison)
{
	return new Batiment(etages, liaison);
}

void Simulation::doAction()
{
	vector<Etage*> etages = this->batiment->getEtages();
	for (int i = 0, max = etages.size(); i < max; i++) {
		vector<Minion*> minions = etages[i]->getMinions();
		vector<Fire*> fires = etages[i]->getFires();
		for (int j = 0, maxJ = minions.size(); j < maxJ; j++) {
			minions[j]->action(etages[i]);
		}
		for (int j = 0, maxJ = fires.size(); j < maxJ; j++) {
			fires[j]->action(etages[i]);
		}
	}
}

Batiment* Simulation::getBatiment() { return this->batiment; }

int Simulation::getNbRemainingMinions() { return this->remainingMinions; }
int Simulation::getNbRemainingPyroman() { return this->remainingPyromane; }
int Simulation::getNbRemainingPompier() { return this->remainingPompier; }
int Simulation::getNbDeadMinions() { return this->deadMinions; }
int Simulation::getNbPanikMinions() { return this->panikMinions; }

int Simulation::getNbFire() { return 0; }

void Simulation::showBatiment()
{
	vector<Etage*> etages = this->batiment->getEtages();
	cout << "W : Wall | w : Wood Wall | F : fire | p : pomier | P : pyromane | E : Entree | S : Sortie | C : PopCorn | X : erreur" << endl << endl;
	for (int i = 0, max = etages.size(); i < max; i++) {
		Etage* e = etages[i];
		for (int x = 0; x < 10; x++) {
			string ligne = "";

			for (int y = 0; y < 10; y++) {
				Case* c = e->getCase(x, y);
				switch (c->getState()) {
				case StateEnum::empty:
					ligne += "   ";
					break;
				case StateEnum::wall:
					if (isSubstateOf(c->getState(), c->getSubState())) {
						if (c->getSubState() == SubStateEnum::wallWood) {
							ligne += " w ";
						}
						else {
							ligne += " W ";
						}
					}
					else {
						ligne += " X ";
					}
					break;
				case StateEnum::flame:
					ligne += " F ";
					break;
				case StateEnum::minion:
					if (isSubstateOf(c->getState(), c->getSubState())) {
						if (c->getSubState() == SubStateEnum::pompier) {
							ligne += " p ";
						}
						else if (c->getSubState() == SubStateEnum::pyroman) {
							ligne += " P ";
						}
						else {
							ligne += " M ";
						}
					}
					else {
						ligne += " X ";
					}
					break;
				case StateEnum::enterDoor:
					ligne += " E ";
					break;
				case StateEnum::exitDoor:
					ligne += " S ";

					break;
				case StateEnum::popCorn:
					ligne += " C ";
					break;
				}
			}
			cout << ligne << endl;
		}
		cout << endl << "------" << endl << endl;
	}
}
