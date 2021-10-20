#include "case.h"
#include "stateEnum.h"
#include "agent.h"
#include <cstddef>
Case::Case(int x, int y){
	this->state = StateEnum::empty;
	this->agent = NULL;
	this->pos_x = x;
	this->pos_y = y;

	this->isPath =false;
	this->f=0;
	this->g=0;
	this->h=0;
	this->parent=NULL;
	this->visited= false;
}

Case::~Case()
{
	if (this->agent != NULL) {
		delete this->agent;
	}
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

int Case::getF(){
	return this->f;
}
int Case::getG(){
	return this->g;
}
int Case::getH(){
	return this->h;
}
void Case::setF(int f){
	this->f = f;
}
void Case::setG(int g){
	this->g = g;
}
void Case::setH(int h){
	this->h = h;
}

void Case::setParent(Case* parent)
{
	this->parent = parent;
}
Case* Case::getParent()
{
	return this->parent;
}

bool Case::getVisited()
{
	return this->visited;
}
void Case::setVisited(bool visited)
{
	this->visited = visited;
}
bool Case::getIsPath()
{
	return this->isPath;
}
void Case::setIsPath(bool isPath)
{
	this->isPath = isPath;
}
// fonction test pour avancer
int Case::distaceHamilton(Case* c1,Case* c2){
	int dx = c1->getX()-c2->getX();
	dx = dx>0?dx:-dx;
	int dy = c1->getY()-c2->getY();
	dy = dy>0?dy:-dy;

	return(dx+dy);
}