#ifndef MIND_H
#define MIND_H

#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "mbtiEnum.h"
using namespace std;

class Mind
{
private:
 string name;
 vector<MBTIEnum> mbti;

public:
	Mind(int seed);

	void readName(int seed);
	void createPersonality(int seed);


	void printMBTI();

};

#endif

