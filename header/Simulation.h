#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <time.h>
#include <random>

#include "fire.h"
#include "pyroman.h"
#include "pompier.h"
#include "batiment.h"



using namespace std;
class Simulation
{

private:
	struct NBbMinionsParam {
		int minStandardEtage, maxStandardEtage;
		int minPompierEtage, maxPompierEtage;
		int minPyromaneEtage, maxPyromaneEtage;
		NBbMinionsParam(int minStandardEtage, int maxStandardEtage, int minPompierEtage, int maxPompierEtage, int minPyromaneEtage, int maxPyromaneEtage) {
			this->minStandardEtage = minStandardEtage;
			this->maxStandardEtage = maxStandardEtage;
			this->minPompierEtage = minPompierEtage;
			this->maxPompierEtage = maxPompierEtage;
			this->minPyromaneEtage = minPyromaneEtage;
			this->maxPyromaneEtage = maxPyromaneEtage;
		}

		NBbMinionsParam(int standardEtage, int pompierEtage, int pyromaneEtage) {
			this->minStandardEtage = this->maxStandardEtage = standardEtage;
			this->minPompierEtage = this->maxPompierEtage = pompierEtage;
			this->minPyromaneEtage = this->maxPyromaneEtage = pyromaneEtage;
		}

		NBbMinionsParam() {
			this->minStandardEtage = this->maxStandardEtage = this->minPompierEtage = this->maxPompierEtage = this->minPyromaneEtage = this->maxPyromaneEtage = 0;
		}
	};

	Batiment* batiment;
	int remainingMinions;
	int remainingPyromane;
	int remainingPompier;
	int deadMinions;
	int panikMinions;
	//Remplace le constructeur de Batiment, set manuellement les cases.
	Batiment* generateBatiment(int nbEtages, int largeur, int hauteur, NBbMinionsParam nbMinions, int start_nbfire, int nb_exits, int nb_enters, int nb_wall, int nb_wood_wall);
	Batiment* generateBatiment(vector<Etage*> cases, vector<liaisonEntreeSortie> liaison);

public:
	Simulation(); //Options : JSON
	~Simulation();

	void doAction(); //fait les actions et rafraichis l'état des minions de ce tour.

	Batiment* getBatiment();

	int getNbRemainingMinions();
	int getNbRemainingPyroman();
	int getNbRemainingPompier();
	int getNbDeadMinions();
	int getNbPanikMinions();

	int getNbFire();

	void showBatiment();
};

#endif