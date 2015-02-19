#ifndef BITADDER_H
#define BITADDER_H

#include <vector>

using namespace std;

class bitAdder
{
public:
	bitAdder() {}
	bitAdder(int length);
	~bitAdder() {}
	// generate all binaries
	bool** genBinaries();
	void printAll();
	// get the binary form of number 'n'
	bool* asBinary(int n) { return allBinaries[n]; }
private:
	// the position of bit for add(); the length of bit
	int pos, length, height;
	// the current binary: for generation; a pointer on a binary bit
	bool *current, *bit;
	// the 2D array of all binaries generated
	bool **allBinaries;
	// print the *current binary
	void printCurrent();
	// increment the current binary by 1
	void add();
};

#endif