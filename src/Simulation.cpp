#include "Simulation.h"

Simulation::Simulation()
{
	this->batiment = Simulation::generateBatiment(3, 10, 10, NBbMinionsParam(1, 1, 1), 1, 1, 1, 1, 1);
}

Simulation::~Simulation() {
	delete batiment;
}

Batiment* Simulation::generateBatiment(int nbEtages, int largeur, int hauteur, NBbMinionsParam nbMinions, int start_nbfire, int nb_exits, int nb_enters, int nb_wall, int nb_wood_wall)
{
	srand(clock());
	vector<Etage*> etages;
	vector<liaisonEntreeSortie> link;
	vector<vector<Case*>> allEntree;
	vector<vector<Case*>> allSortie;

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
			if (counterPomp < nbStdMinions) {
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
			if (counterPyro < nbStdMinions) {
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
		etages.push_back(new Etage(minions, fires, cases, entrees, sorties));
		allEntree.push_back(entrees);
		allSortie.push_back(sorties);

	}

	for (int i = nbEtages - 1; i >= 0; i--) {
		if (i == nbEtages - 1) {
			for (int j = 0, max = allEntree[i].size(); j < max; j++) {
				link.push_back(liaisonEntreeSortie(allEntree[i][j], nullptr));
			}
		}

		if (i == 0) {
			for (int j = 0, max = allSortie[i].size(); j < max; j++) {
				link.push_back(liaisonEntreeSortie(nullptr, allSortie[i][j]));
			}
		}
		else
		{
			for (int j = 0, max = allSortie[i].size(); j < max; j++) {
				for (int k = 0, maxk = allEntree[i - 1].size(); k < maxk; k++) {
					link.push_back(liaisonEntreeSortie(allSortie[i][j], allEntree[i - 1][k]));
				}
			}
		}
	}
	return new Batiment(etages, link);
}

Batiment* Simulation::generateBatiment(vector<Etage*> etages, vector<liaisonEntreeSortie> liaison)
{
	return new Batiment(etages, liaison);
}

void Simulation::doAction()
{
}

Batiment* Simulation::getBatiment() { return this->batiment; }

int Simulation::getNbRemainingMinions() { return this->remainingMinions; }
int Simulation::getNbRemainingPyroman() { return this->remainingPyromane; }
int Simulation::getNbRemainingPompier() { return this->remainingPompier; }
int Simulation::getNbDeadMinions() { return this->deadMinions; }
int Simulation::getNbPanikMinions() { return this->panikMinions; }

int Simulation::getNbFire() { return 0; }