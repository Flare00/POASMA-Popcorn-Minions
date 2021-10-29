#include"pompier.h"
#include "batiment.h"
#include "minion.h"
#include "case.h"
#include "fire.h"
#include <iostream>
using namespace std;
#define PROPAGATION_CHANCE 3

Pompier::Pompier(int x,int y):Minion(x,y){}
										  					
//etient le feu que se trouve à la case <-c->
void Pompier::eteintFeu(Case* c,Batiment* batiment){
	//int x=c->getY();
	//int y=c->getX();
	if(c != NULL){
		if(c->getState() == StateEnum::flame){
				c->setState(StateEnum::empty);
				delete c->getAgent();
				c->setAgent(NULL);				
		}
	}
}
void Pompier::move(Batiment* batiment,int x, int y){
	Case* emplacement = batiment->getCase(x,y); //la position donnée en entrer
	if (emplacement != NULL) {
		Case* currentCase = batiment->getCase(this->getX(), this->getY());// ma position actuelle 
		switch (emplacement->getState()) {
			case StateEnum::empty :
				emplacement->setState(StateEnum::pompier);
				emplacement->setAgent(this);
				this->setX(x);
				this->setY(y);
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
				break;
			case StateEnum::flame :
				emplacement->setState(StateEnum::popCorn);
				delete emplacement->getAgent();
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
				delete this;
				break;
			case StateEnum::exitDoor :
				currentCase->setState(StateEnum::empty);
				currentCase->setAgent(NULL);
				delete this;
				break;
		}
	}
}


void Pompier::action(Batiment* batiment){

	//this->move(batiment, dx, dy);
	int direction = (rand() % 4);
		this->direction = direction;
	switch(direction){
		case 0:
			this->move(batiment, this->getX(),this->getY()+1);
			for(int i = 0; i < this->porteeLance; i++){
 				this->eteintFeu(batiment->getCase(this->getX(),this->getY() +i), batiment);
			}

		break;
		case 1:
			this->move(batiment, this->getX()+1,this->getY());
			for(int i = 0; i < this->porteeLance; i++){
 				this->eteintFeu(batiment->getCase(this->getX()+i,this->getY()), batiment);
			}
		break;
		case 2:
			this->move(batiment, this->getX(),this->getY()-1);
			for(int i = 0; i < this->porteeLance; i++){
 				this->eteintFeu(batiment->getCase(this->getX(),this->getY() -i), batiment);
			}

		break;
		case 3:
			this->move(batiment, this->getX()-1,this->getY());
			for(int i = 0; i < this->porteeLance; i++){
 				this->eteintFeu(batiment->getCase(this->getX()-i,this->getY()), batiment);
			}
		break;
	}



	
}