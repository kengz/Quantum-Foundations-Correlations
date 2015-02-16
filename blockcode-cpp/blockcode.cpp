#include "blockcode.h"
#include <iostream>

///////////////////////////
// convert all to bitset //
///////////////////////////

/**
 * The BlockCode(BC) class.
 * Pass an original BC,
 * transform, then return the transformed data,
 * repeat for versions of transformations, (ptr-reset, old data not deleted)
 */

//////////////////
// Constructors //
//////////////////
/**
 * Default BC constructor.
 * @param X the # of columns
 * @param Y the # of rows
 * @param data The binary data, BC bijected to 1D array.
 */
 BlockCode::BlockCode(int X, int Y, bool *data): sizeX(X), sizeY(Y), len(X*Y)
 {
	// initilize flip to all false = unflip. All init to false = 0.
 	flipper = new bool[X];
 	memset(flipper, 0, X);

	// fill array with index value
 	indexX = new int[X];
 	for (int i = 0; i < X; i++)
 		indexX[i] = i;

 	indexY = new int[Y];
 	for (int i = 0; i < Y; i++)
 		indexY[i] = i;

	// set and store data
 	this->data = data;
 	// store raw data as the first instance
 	instances.push_back(this->data);
 }
/**
 * Constructor for testing purposes. Init data to all false = 0.
 */
 BlockCode::BlockCode(int X, int Y): BlockCode(X, Y, new bool[X*Y]) {
 	memset(data, 0, X*Y);
 }

 BlockCode::~BlockCode() {
 	delete [] indexX;
 	delete [] indexY;
 	delete [] flipper;
 }

////////////////
// Operations //
////////////////
///All transformations are virtualy represented using 3 arrays: indexX, indexY, flipper.
///Swapping is done by reassigning indices of rows and columns, i.e. the value at index is its actual position after transformation; binary column flipping by recording which index is flipped.
///A copy of the transformed data is constructed from data and these arrays

/** Virtually swap columns: record the change of indices */
 void BlockCode::swapX(int x1, int x2)
 {
 	int tmp = indexX[x1];
 	indexX[x1] = indexX[x2];
 	indexX[x2] = tmp;
 }
/** Virtually swap rows: record the change of indices */
 void BlockCode::swapY(int y1, int y2)
 {
 	int tmp = indexY[y1];
 	indexY[y1] = indexY[y2];
 	indexY[y2] = tmp;
 }
/** Virtually binary-flip a column at x */
 void BlockCode::flip(int x)
 {
 	flipper[x] += true;
 }


//////////////////////////
// Bijection, transform //
//////////////////////////
/** Return the position of entry after the transformation */
 int BlockCode::hash(int x, int y)
 {
 	return sizeX * indexY[y] + indexX[x];
 }

/**
 * Construct the transformed data from the original data and indexX, indexY, flipper
 * Repoint ptr *tData to the newly constructed BC, save it as an instance of BC
 * @return tData Pointer to this new BC
 */
 bool* BlockCode::makeTData()
 {
 	cout << "Applying transformation to data." << endl << endl;
 	// reset pointer to empty data
 	tData = new bool[len];
 	memset(tData, 0, len);
 	size_t size = 0;

 	// traverse and construct new transformed matrix
 	for (int y = 0; y < sizeY; y++) {
 		for (int x = 0; x < sizeX; x++) {
 			int i = hash(x, y);
 			// save the flipped the binary data
 			tData[size++] = data[i] + flipper[ indexX[x] ];
 		}
 	}
 	// then store this instance made
 	instances.push_back(tData);
 	// finally, return this instance of transformed data, not deleted later
 	return tData;
 }

//////////////
// printers //
//////////////

/** print the operations */
 void BlockCode::printOps(char c)
 {
 	switch(c) {
 		case 'X': {
 			cout << "Swapped x-indices: " << endl;
 			for (int i = 0; i < sizeX; i++)
 				cout << indexX[i];
 			break;
 		}
 		case 'Y': {
 			cout << "Swapped y-indices: " << endl;
 			for (int i = 0; i < sizeY; i++)
 				cout << indexY[i];
 			break;
 		}
 		case 'F': {
 			cout << "Flipped columns: " << endl;
 			for (int i = 0; i < sizeX; i++)
 				cout << flipper[i];
 			break;
 		}
 		default: {
 			cout << "Invalid printOps, try X, Y or F";
 			break;
 		}
 	}
 	cout << endl << endl;
 }
/** print an instance of the BC */
 void BlockCode::printBC(int which)
 {
 	if (-1 < which && which < instances.size())
 	{
 		cout << "BlockCode inst. " << which << ":" << endl;
 		// format BC
 		int i = 0;
 		for (int y = 0; y < sizeY; y++) {
 			for (int x = 0; x < sizeX; x++) {
 				// get this instance, access each entry i
 				cout << (instances[which])[i];
 				i++;
 			}
 			cout << endl;
 		}
 		cout << endl;
 	}
 	else
 		cout << "Invalid index, try 0–" << instances.size()-1 << endl;
 }

/** Match two instances of BC, return boolean. */
 bool BlockCode::matchBC(int i, int j)
 {
 	bool match = true;
 	for (int k = 0; k < len; ++k) {
 		// compare each term of instances i and j
 		if ( (instances[i])[k] != (instances[j])[k] ) {
 			match = false;
 		}
 	}
 	if (match)
 		cout << "Match: BC " << i << "," << j << endl;
 	else
 		cout << "Not-Match: BC " << i << "," << j << endl;
 	return match;
 }


 void test()
 {
 	BlockCode *bc = new BlockCode(4,3);
 	bc->printBC(0);
 	bc->flip(1);
 	bc->makeTData();
 	bc->swapX(0,1);
 	bc->makeTData();
 	bc->swapX(0,2);
 	bc->makeTData();
 	bc->swapX(0,3);
 	bc->makeTData();
 	bc->printBC(0);
 	bc->printBC(1);
 	bc->printBC(2);
 	bc->printBC(3);
 	bc->printBC(4);
 	bc->matchBC(3,4);
 	bc->matchBC(2,4);
 }

 int main()
 {
 	test();	

 	return 0;
 }