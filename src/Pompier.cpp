#include"pompier.h"
#include <iostream>
using namespace std;
#define PROPAGATION_CHANCE 3

Pompier::Pompier(int x, int y) :Minion(x, y) {}

//etient le feu que se trouve à la case <-c->
void Pompier::eteintFeu(Case* c, Etage* etage) {
	//int x=c->getY();
	//int y=c->getX();
	if (c != NULL) {
		if (c->getState() == StateEnum::flame) {
			c->setState(StateEnum::empty);
			etage->kill(c->getAgent(), false);
			c->setAgent(NULL);
		}
	}
}
void Pompier::move(Etage* etage, int x, int y) {
	cout << "Move pompier" << endl;
		Case* emplacement = etage->getCase(x, y); //la position donnée en entrer
		if (emplacement != NULL) {
			Case* currentCase = etage->getCase(this->getX(), this->getY());// ma position actuelle 
			switch (emplacement->getState()) {
			case StateEnum::empty:
				emplacement->setState(StateEnum::minion);

				emplacement->setSubState(SubStateEnum::pompier);
				emplacement->setAgent(this);
				this->setX(x);
				this->setY(y);
				currentCase->setState(StateEnum::empty);
				currentCase->setSubState(SubStateEnum::subEmpty);
				currentCase->setAgent(NULL);
				break;
			case StateEnum::flame:
				emplacement->setState(StateEnum::popCorn);
				emplacement->setSubState(SubStateEnum::subEmpty);
				etage->kill(emplacement->getAgent(), false);
				currentCase->setState(StateEnum::empty);
				emplacement->setSubState(SubStateEnum::subEmpty);
				currentCase->setAgent(NULL);
				this->popcorn(etage);
				break;
			case StateEnum::exitDoor:
				currentCase->setState(StateEnum::empty);
				emplacement->setSubState(SubStateEnum::subEmpty);
				currentCase->setAgent(NULL);
				etage->kill((Agent *)this, true);
				break;
			}
	}
}


void Pompier::action(Etage* etage) {

	//this->move(etage, dx, dy);
	int direction = (rand() % 4);
	this->direction = direction;
	switch (direction) {
	case 0:
		this->move(etage, this->getX(), this->getY() + 1);
		for (int i = 0; i < this->porteeLance; i++) {
			this->eteintFeu(etage->getCase(this->getX(), this->getY() + i), etage);
		}

		break;
	case 1:
		this->move(etage, this->getX() + 1, this->getY());
		for (int i = 0; i < this->porteeLance; i++) {
			this->eteintFeu(etage->getCase(this->getX() + i, this->getY()), etage);
		}
		break;
	case 2:
		this->move(etage, this->getX(), this->getY() - 1);
		for (int i = 0; i < this->porteeLance; i++) {
			this->eteintFeu(etage->getCase(this->getX(), this->getY() - i), etage);
		}

		break;
	case 3:
		this->move(etage, this->getX() - 1, this->getY());
		for (int i = 0; i < this->porteeLance; i++) {
			
			this->eteintFeu(etage->getCase(this->getX() - i, this->getY()), etage);
		}
		break;
	}




}