#ifndef BLOCKCODE_H
#define BLOCKCODE_H

#include <vector>

using namespace std;

class BlockCode
{
public:
	BlockCode(int X, int Y, bool *data);
	BlockCode(int X, int Y);
	~BlockCode();
	// 3 operations
	void swapX(int x1, int x2);
	void swapY(int y1, int y2);
	void flip(int x);
	// bijection
	int hash(int x, int y);
	// make and store to instances a BC instance *tData is pointing to
	bool* makeTData();
	// printers
	void printOps(char);
	void printBC(int);
	// match BC
	bool matchBC(int i, int j);

private:
	int sizeX, sizeY, len;
	// storing the operations
	int *indexX, *indexY;
	bool *flipper;
	// The original data (untransformed)
	bool *data;
	// an instance of transformed data: 
	bool *tData;
	// Vector of instances of BC
	vector<bool*> instances;
};

#endif