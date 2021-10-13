#include "minion.h"
Minion::Minion(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}
void Minion::action(Batiment* batiment){

}
void Minion::move(int x, int y){
	
}
void Minion::idle(){
	
}
void Minion::panik(){
	
}
void Minion::popcorn(){
	delete this;
}