#ifndef PARSEFRI_H
#define PARSEFRI_H

#include "bitadder.h"
#include <string>
#include <vector>

using namespace std;

class parseFri
{
public:
	parseFri();
	~parseFri() {}
	void readSrc(int);
	void makeBC();
private:
	vector<string> src, tar;
	// the BC in Fripertinger's coefficient form
	vector<int> *coef;
	int X, Y, Z;
	bitAdder *ba;
	
};
#endif