#include "blockcode.h"
#include <iostream>
#include <iterator>

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
 * len = X*Y = num of entries in BC
 * @param data The binary data, BC bijected to 1D array.
 */
 BlockCode::BlockCode(int X, int Y, int *data): sizeX(X), sizeY(Y), len(X*Y)
 {
 	// set the max number of instances computed/stored
 	// const int MAX_INSTANCES = 2000000;

 	// init instances 2D array; 
 	instances = new int*[MAX_INSTANCES];
 	for (int i = 0; i < MAX_INSTANCES; ++i)
 	{
 		instances[i] = new int[len];
 		memset(instances[i], 0, sizeof(int)*len);
 	}
 	// save data
 	this->data = data;
 	// init number of instances, start from 0
 	numInst = 1;
 	// store raw data as the first instance
 	for (int i = 0; i < len; ++i)
 		instances[0][i] = this->data[i];

 	// init pointers
 	indexX = new vector<int>; indexY = new vector<int>;
 	flipper = new bool[sizeX];
 	resetOps();

 }
/**
 * Constructor for testing purposes. Init data to all false = 0.
 */
 BlockCode::BlockCode(int X, int Y): BlockCode(X, Y, new int) {
 	memset(data, 0, sizeof(int)* X*Y);
 }

 void BlockCode::resetOps()
 {
 	// fill array with index value = identity perm
 	delete indexX;
 	indexX = new vector<int>;
 	for (int i = 0; i < sizeX; i++)
 		indexX->push_back(i);

 	delete indexY;
 	indexY = new vector<int>;
 	for (int i = 0; i < sizeY; i++)
 		indexY->push_back(i);

	// initilize flip to all false = unflip. All init to false = 0.
 	delete flipper;
 	flipper = new bool[sizeX];
 	memset(flipper, 0, sizeof(bool) * sizeX);
 	// init bitAdder; binaries generated later only when needed
 	ba = bitAdder(sizeX);
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
 	int tmp = (*indexX)[x1];
 	(*indexX)[x1] = (*indexX)[x2];
 	(*indexX)[x2] = tmp;
 }
/** Virtually swap rows: record the change of indices */
 void BlockCode::swapY(int y1, int y2)
 {
 	int tmp = (*indexY)[y1];
 	(*indexY)[y1] = (*indexY)[y2];
 	(*indexY)[y2] = tmp;
 }
/** Virtually binary-flip a column at x */
 void BlockCode::flip(int x)
 {
 	flipper[x] ^= 1;
 }


//////////////////////////
// Bijection, transform //
//////////////////////////
/** Return the position of entry after the transformation */
 int BlockCode::hash(int x, int y)
 {
 	return sizeX * (*indexY)[y] + (*indexX)[x];
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
 				cout << (*indexX)[i];
 			break;
 		}
 		case 'Y': {
 			cout << "Swapped y-indices: " << endl;
 			for (int i = 0; i < sizeY; i++)
 				cout << (*indexY)[i];
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
 	if (-1 < which && which < numInst ) {
 		cout << "BC inst. " << which << "." << endl;
		// format BC
 		int nextline = 1;
 		for (int i = 0; i < len; ++i)
 		{
 			cout << instances[which][i] << " ";
 			if (nextline++ % sizeX == 0) cout << endl;

 		}  
 		cout << endl;
 	}
 	else
 		cout << "Invalid index, try 0–" << numInst-1 << endl;
 }


//////////////////////////////////////////////////
// BC Classification and brute force generation //
//////////////////////////////////////////////////
/** Match instance-i of this BC with otherData BC, return boolean. */
 bool BlockCode::matchBC(int i, int *otherData)
 {
 	bool match = true;
 	for (int k = 0; k < len; ++k) {
		// compare instances i and otherData, break immediately upon mismatch
 		if ( instances[i][k] != otherData[k] ) {
 			match = false;
 			break;
 		}
 	}
 	if (match)
 		cout << "==Match:==\t";
 	else
 		cout << "Not-Match:\t";
 	return match;
 }

/** find a match to BC by brute force; must gen. all BC instances first. */
 bool BlockCode::bruteForce(int *otherData)
 {
	// finally, compare all instances to the original
 	for (int i = 0; i < numInst; ++i)
 	{
		// once find a match, print it, end loop, return true
 		bool match = matchBC(i, otherData);
 		printBC(i);
 		if ( match )
 			return true;
 	}

	// if exhaustively find none, return false;
 	cout << "No match found by bruteForce()" << endl;
 	return false;
 }

/** 
 * Generate all nonredundant BC instances for bruteForce()
 * Try: X-swaps, Y-swaps, flip.
 */
 void BlockCode::genAllInstances()
 {
 	// Reset:
	// clear instances except original
 	for(int i = 1; i < numInst; ++i)
 		memset(instances[i], 0, sizeof(int)*len);
 	// and reset all ops
 	resetOps();
 	printOps('X');
 	printOps('Y');
 	printOps('F');
	// generate all binaries for flipper permutations
 	ba.genBinaries();

 	// try all binaries for flipper
 	int countX = 0;
 	cout << "ba height: " << ba.getHeight() << endl;
 	for(int i = 0; i < ba.getHeight(); i++ ) {
 		if (numInst > MAX_INSTANCES) {
 			cout << "Exceed max instances allocated. Quit bruteForce()." << endl;
 			break;
 		}
 		flipper = ba.asBinary(i);
		// do for each index permutation of X and Y
 		do {
 			if (numInst > MAX_INSTANCES)
 				break;
 			do {
 				countX++;
 				printOps('X');
				// if there's more space, compute instance and save
 				if (numInst > MAX_INSTANCES)
 					break;
 				makeTData();

 			} while (next_permutation( (*indexX).begin(), (*indexX).end() ));
 		} while (next_permutation( (*indexY).begin(), (*indexY).end() ));
 	}
 	cout << "countX: " << countX << endl;
 }

/**
 * Construct the transformed data from the original data and indexX, indexY, flipper
 * Repoint ptr tData to the newly constructed BC, save it as an instance of BC
 * @return tData Pointer to this new BC
 */
 void BlockCode::makeTData()
 {
 	// get fresh array of all 0 for transformation, to be saved – no waste.
 	int trans[len];
 	tData = trans;
 	memset(tData, 0, sizeof(int) * len);

 	int size = 0;
	// traverse and construct new transformed matrix
 	for (int y = 0; y < sizeY; y++) {
 		for (int x = 0; x < sizeX; x++) {
 			int i = hash(x, y);
			// save the flipped the binary data
 			tData[size] = ( data[i] + flipper[ (*indexX)[x] ] ) %2;
 			size++;
 		}
 	}
	// then store this instance, increment numInst by 1
 	for (int i = 0; i < len; ++i)
 		instances[numInst][i] = tData[i];
 	numInst++;
 }



/** Deprecated: Gray code = generate binary strings of len n, saved to bins. */
// void BlockCode::genGray(int n, bool print)
// {
//     // base case
//     if (n <= 0)
//         return;

//     // start with one-bit pattern
//     bins.push_back(vector<int>{0});
//     bins.push_back(vector<int>{1});

//     // Every iteration of this loop generates 2*i codes from previously
//     // generated i codes.

//     int i, j;
//     for (i = 2; i < (1<<n); i = i<<1)
//     {
//     // Enter the prviously generated codes again in bins[] in reverse
//     // order. Nor bins[] has double number of codes.
//         for (j = i-1 ; j >= 0 ; j--)
//             bins.push_back(bins[j]);

//         // append 0 to the first half
//         for (j = 0 ; j < i ; j++)
//             bins[j].push_back(0);

//         // append 1 to the second half
//         for (j = i ; j < 2*i ; j++)
//             bins[j].push_back(1);

//     }

//     // default print=false; option to print the generated Gray code
//     if (print)
//     {
//      // print contents of bins[]
//      for (i = 0 ; i < bins.size() ; i++ )
//         for (int j = 0; j < bins[i].size(); ++j)
//            cout << bins[i][j];
//        cout << endl;

//    }

// }



 void test()
 {
 	// int arr[9] = {1,1,1,1,0,1,1,1,1};
 	int arr[4] = {0,0,0,0};
 	int *ptr = arr;
 	BlockCode bc = BlockCode(2,2,ptr);
 	// bc.test();
 	bc.genAllInstances();
 	cout << "num of inst: " << bc.getNumInst() << endl;
 	for (int i = 0; i < bc.getNumInst(); ++i)
 	{
 		bc.printBC(i);
 	}
 	// bc.printBC(0);
 	// bc.printBC(1);
 	// bc.printBC(2);
 	// bc.printBC(3);
	// cout << "calling brute force: " << endl;
	// bc.bruteForce(arr2);
 }

 int main()
 {
	// cout << sizeof();
 	test();	

 	return 0;
 }
