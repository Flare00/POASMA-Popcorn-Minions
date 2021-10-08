#include "case.h"
Case::Case(){
	this->state = StateEnum::empty;
	this->agent = NULL;
}
Case::StateEnum getState(){
	return this->state;
}
Case::void setState(StateEnum state){
	this->state = state;
}
Case::Agent getAgent(){
	return this->agent;
}
Case::void setAgent(Agent agent){
	this->agent = agent;
}