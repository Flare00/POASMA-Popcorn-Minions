#include "batiment.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){
	Batiment * bat = new Batiment(10, 10, 1, 1, 1 ,10);
	cout << "o : minions - | : murs - f : feu - e : sortie";
	for(int j = 0; j < bat->getHeight(); j++){
		cout << endl << " ";
		for(int i = 0; i < bat->getWidth(); i++){
			switch(bat->getState(i,j)){
				case StateEnum::minion :
					cout << "o ";
					break;
				case StateEnum::wall :
					cout << "| ";
					break;
				case StateEnum::flame :
					cout << "f ";
					break;
				case StateEnum::exitDoor :
					cout << "e ";
					break;
				case StateEnum::empty :
					cout << "  ";
					break;
			}
		}
	}
	cout << std::endl;
	delete bat;
	return 0;
}

