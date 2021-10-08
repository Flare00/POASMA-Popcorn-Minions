#include "agent.h"
Agent::Agent(){
	this->pos_x = 0;
	this->pos_y = 0;
}
Agent::Agent(int x, int y){
	this->pos_x = x;
	this->pos_y = y;
}
Agent::~Agent(){
}
	
int Agent::getX(){
	return this->pos_x;
}
int Agent::getY(){
	return this->pos_y;
}
void Agent::setX(int x){
	this->pos_x = x;
}
void Agent::setY(int y){
	this->pos_y = y;
}
