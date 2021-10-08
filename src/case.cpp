#include "case.h"
#include "stateEnum.h"
#include "agent.h"

Case::Case(){
	this->state = StateEnum::empty;
}

void Case::setState(StateEnum state){
	this->state = state;
}
Agent Case::getAgent(){
	return this->agent;
}
void Case::setAgent(Agent agent){
	this->agent = agent;
}

StateEnum Case::getState(){
	return this->state;
}