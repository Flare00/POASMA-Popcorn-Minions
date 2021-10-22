#include "Mind.hpp"
#include <iostream>
#include <fstream>
#include <time.h>

Mind::Mind(int seed){

  this->readName(seed);

  cout << "Bonjour créateur !" << '\n';
  cout << "Je m'appelle " << this->name  << '\n';
  this->createPersonality(seed);
  this->printMBTI();
  
}
void Mind::readName(int seed)
{
  string line;
  int i=0;
  
  ifstream myfile ("ressources/name.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line))
    {
      if(i==seed%1000)
      {
        this->name=line;
      }
      i++;
    }

    myfile.close();
  }

}
void Mind::createPersonality(int seed)
{
  int seedPersonality = seed%16;
  this->mbti.resize(4);


  if(seedPersonality%2)
    this->mbti[0]=E;
  else
    this->mbti[0]=I;

  seedPersonality= seedPersonality>>1;

  if(seedPersonality%2)
    this->mbti[1]=S;
  else
    this->mbti[1]=N;

  seedPersonality=seedPersonality>>1;


  if(seedPersonality%2)
    this->mbti[2]=T;
  else
    this->mbti[2]=F;

  seedPersonality=seedPersonality>>1;

  if(seedPersonality%2)
    this->mbti[3]=J;
  else
    this->mbti[3]=P;
  
  
  }
void Mind::printMBTI()
{
  cout << "Mon test MBTI est ";
  for(int i=0;i<4;i++)
  {
    switch(this->mbti[i])
    {
      case E:
      cout<<"E";
      break;

      case I:
      cout<<"I";
      break;

      case S:
      cout<<"S";
      break;
      
      case N:
      cout<<"N";
      break;
      
      case T:
      cout<<"T";
      break;

      case F:
      cout<<"F";
      break;

      case J:
      cout<<"J";
      break;
      case P:
      cout<<"P";
      break;

    }
  }
  cout<<endl;

}
