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
	void printBC(int);
	void makePrimeBC();
	void compareBC();
private:
	int X, Y, Z;
	int** inputBC;
	// BlockCode *prime;
	BlockCode prime;
	// handler submethods
	void menu();
	void getBC(int);
	void getDim();
	// BC submethods
	
	
	
};

#endif