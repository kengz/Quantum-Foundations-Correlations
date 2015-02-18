#ifndef PARSEFRI_H
#define PARSEFRI_H
#include "bitadder.h"
#include <string>

using namespace std;

class parseFri
{
public:
	parseFri();
	~parseFri();
private:
	int X, Y, Z;
	// bitAdder ba;
	int *coef;
	string files;
};
#endif