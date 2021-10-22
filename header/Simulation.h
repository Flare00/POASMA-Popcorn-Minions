#ifndef SIMULATION_H
#define SIMULATION_H

#include "batiment.h"
#include "case.h"
#include <vector>

using namespace std;
class Simulation{

private : 
	Batiment * batiment;
	int remainingMinions;
	int remainingPyromane;
	int remainingPompier;
	int deadMinions;
	int panikMinions;
	//Remplace le constructeur de Batiment, set manuellement les cases.
	Batiment* generateBatiment(int nbEtages, int largeur, int hauteur, int start_nbminion, int start_nbfire, int nb_exits ,int nb_wall);
	Batiment* generateBatiment(vector<Etage> cases);
public:
	Simulation(String options); //Options : JSON
	~Simulation();
	
	void doAction(); //fait les actions et rafraichis l'état des minions de ce tour.
	
	Batiment* getBatiment();
	
	int getNbRemainingMinions();
	int getNbRemainingPyroman();
	int getNbRemainingPompier();
	int getNbDeadMinions();
	int getNbPanikMinions();
	
	int getNbFire();
	
}

#endif