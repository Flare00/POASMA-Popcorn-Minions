	Simulation::Simulation(String options){
	}
	~Simulation::Simulation(){}
	Batiment* generateBatiment(int nbEtages, int largeur, int hauteur, int start_nbminion, int start_nbfire, int nb_exits ,int nb_wall){

	}
	Batiment* generateBatiment(vector<Etage> cases){
		
	}
	void Simulation::doAction(){
	}
	
	Batiment* Simulation::getBatiment(){return this->batiment;}
	
	int Simulation::getNbRemainingMinions(){ return this->remainingMinions}
	int Simulation::getNbRemainingPyroman(){return this->remainingPyromane}
	int Simulation::getNbRemainingPompier(){return this->remainingPompier}
	int Simulation::getNbDeadMinions(){return this->deadMinions}
	int Simulation::getNbPanikMinions(){return this->panikMinions}
	
	int Simulation::getNbFire(){}