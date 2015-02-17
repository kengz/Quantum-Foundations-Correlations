#ifndef CANON_H
#define CANON_H
#include "blockcode.h"

class BlockCode;

class Canon
{
public:
	Canon() {}
	~Canon(){}
	void handler();
	void runBC();
private:
	int X, Y, Z;
	vector<vector<int>*> vecBC;
	BlockCode *prime;
	// handler submethods
	void menu();
	vector<int>* getBC();
	void getDim();
	// BC submethods
	void makePrimeBC();
	void compareBC();
	void printBC(int);
	
};

#endif