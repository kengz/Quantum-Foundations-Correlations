#ifndef CANON_H
#define CANON_H

#include "blockcode.h"

class BlockCode;

class Canon
{
public:
	Canon() {}
	~Canon(){}
	// handles IO
	void handler();
	// run BC generation and comparison
	void runBC();
	void printBC(int);
private:
	// BC width, height, and number of BC being entered
	int X, Y, Z;
	// storage. each row is a BC, stored as 1D array
	int** inputBC;
	// the primary BC object
	BlockCode prime;
	// handler submethods
	void menu();
	void getBC(int);
	void getDim();
	// BC submethods
	void makePrimeBC();
	void compareBC();
	
};

#endif