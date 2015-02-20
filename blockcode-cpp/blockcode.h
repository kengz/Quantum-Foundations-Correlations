#ifndef BLOCKCODE_H
#define BLOCKCODE_H

#include "bitadder.h"

using namespace std;

class BlockCode
{
public:
	BlockCode() {}
	BlockCode(int X, int Y, int *data);
	BlockCode(int X, int Y);
	~BlockCode() {}
	// 3 operations
	void swapX(int x1, int x2);
	void swapY(int y1, int y2);
	void flip(int x);
	void resetOps();
	// bijection
	int hash(int x, int y);
	// make and store an instance of tData to instances
	void makeTData();
	int getNumInst() { return numInst; }
	// printers
	void printOps(char);
	void printBC(int);
	// match i-instance of this BC and *otherData
	bool matchBC(int i, int *otherData);
	// brute force methods. Must immediately follow constructor.
	bool bruteForce(int *otherData);
	void genAllInstances();
	// deprecated, Grey code, replaced by bitAdder
	// void genGray(int, bool print = false);

private:
	// width, height, and BC size
	int sizeX, sizeY, len;
	// indices permutation. vector to use next_permutation
	vector<int> *indexX, *indexY;
	// column flipper
	bool *flipper;
	// binary string generator, for flipper
	bitAdder ba;
	// The original *data, size = len (untransformed)
	int *data;
	// an instance of transformed data, size = len 
	int *tData;
	// Vector of instances of BC = array of tData
	int** instances;
	// the number of instances
	int numInst;
	// max instances allocated in memory
	int MAX_INSTANCES;

};

#endif