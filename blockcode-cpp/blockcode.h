#ifndef BLOCKCODE_H
#define BLOCKCODE_H

#include <vector>

using namespace std;

class BlockCode
{
public:
	BlockCode(int X, int Y, vector<int> *data);
	BlockCode(int X, int Y);
	~BlockCode();
	// 3 operations
	void swapX(int x1, int x2);
	void swapY(int y1, int y2);
	void flip(int x);
	// bijection
	int hash(int x, int y);
	// make and store to instances a BC instance tData is pointing to
	vector<int>* makeTData();
	// printers
	void printOps(char);
	void printBC(int);
	// match BC: difference instances i,j of the same BC
	bool matchBC(int i, int j);
	// match i-instance of this BC and *otherData
	bool matchBC(int i, vector<int> *otherData);
	// brute force methods. Must immediately follow constructor.
	bool bruteForce(vector<int> *otherData);
	void genAllInstances();
	void genGray(int, bool print=false);

private:
	int sizeX, sizeY, len;
	// storing the operations
	vector<int> *indexX, *indexY;
	vector<int> *flipper;
	// bins store all generated binary codes for bruteforce()
	vector< vector<int> > bins;
	// The original *data (untransformed)
	vector<int> *data;
	// an instance of transformed *data: 
	vector<int> *tData;
	// Vector of instances of BC
	vector<vector<int>*> instances;
};

#endif