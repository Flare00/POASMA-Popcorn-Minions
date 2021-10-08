#include "case.h"
#include "stateEnum.h"
#include "agent.h"

Case::Case(int x, int y){
	this->state = StateEnum::empty;
	this->pos_x = x;
	this->pos_y = y;
}

StateEnum Case::getState(){
	return this->state;
}

void Case::setState(StateEnum state){
	this->state = state;
}
Agent *Case::getAgent(){
	return this->agent;
}
void Case::setAgent(Agent *agent){
	this->agent = agent;
}

int Case::getX(){
	return this->pos_x;
}
int Case::getY(){
	return this->pos_y;
}
void Case::setX(int x){
	this->pos_x = x;
}
void Case::setY(int y){
	this->pos_y = y;
}

