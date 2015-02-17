#include "blockcode.h"
#include <iostream>
#include <algorithm>
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
 * @param data The binary data, BC bijected to 1D array.
 */
 BlockCode::BlockCode(int X, int Y, vector<int> *data): sizeX(X), sizeY(Y), len(X*Y)
 {
	// initilize flip to all false = unflip. All init to false = 0.
 	// flipper = new int[X];
 	flipper = new vector<int>(X,0);
 	// memset(flipper, 0, X);

	// fill array with index value
 	indexX = new vector<int>;
 	for (int i = 0; i < X; i++)
 		indexX->push_back(i);

 	// indexY = new int[Y];
 	indexY = new vector<int>;
 	for (int i = 0; i < Y; i++)
 		indexY->push_back(i);

	// set and store data by passing ptr
 	this->data = data;
 	// store raw data as the first instance
 	instances.push_back(this->data);
 }
/**
 * Constructor for testing purposes. Init data to all false = 0.
 */
 BlockCode::BlockCode(int X, int Y): BlockCode(X, Y, new vector<int>) {
 	// memset(data, 0, sizeof(int)* X*Y);
 }

 BlockCode::~BlockCode() {
 	// delete [] indexX;
 	// delete [] indexY;
 	// delete [] flipper;
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
 	(*flipper)[x] = ( (*flipper)[x] + 1) % 2;
 }


//////////////////////////
// Bijection, transform //
//////////////////////////
/** Return the position of entry after the transformation */
 int BlockCode::hash(int x, int y)
 {
 	return sizeX * (*indexY)[y] + (*indexX)[x];
 }

/**
 * Construct the transformed data from the original data and indexX, indexY, flipper
 * Repoint ptr tData to the newly constructed BC, save it as an instance of BC
 * @return tData Pointer to this new BC
 */
 vector<int>* BlockCode::makeTData()
 {
 	// cout << "Applying transformation to data." << endl;
 	// reset pointer to empty data
 	tData = new vector<int>(len,0);
 	// memset(tData, 0, len);
 	
 	size_t size = 0;
 	// traverse and construct new transformed matrix
 	for (int y = 0; y < sizeY; y++) {
 		for (int x = 0; x < sizeX; x++) {
 			int i = hash(x, y);
 			// save the flipped the binary data
 			(*tData)[size++] = ( (*data)[i] + (*flipper)[ (*indexX)[x] ]) % 2;
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
 				cout << (*flipper)[i];
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
 	if (-1 < which && which < instances.size() ) {
 		cout << "BC inst. " << which << "." << endl;
 		// format BC
 		int i = 0;
 		for (int y = 0; y < sizeY; y++) {
 			for (int x = 0; x < sizeX; x++) {
 				// get this instance, access each entry i
 				cout << (*instances[which])[i] << " ";
 				i++;
 			}
 			cout << endl;
 		}
 		cout << endl;
 	}
 	else
 		cout << "Invalid index, try 0–" << instances.size()-1 << endl;
 }


//////////////////////////////////////////////////
// BC Classification and brute force generation //
//////////////////////////////////////////////////
/** Match two instances of this BC, return boolean. */
 bool BlockCode::matchBC(int i, int j)
 {
 	bool match = true;
 	for (int k = 0; k < len; ++k) {
 		// compare each term of instances i and j
 		if ( (instances[i])[k] != (instances[j])[k] ) {
 			match = false;
 			break;
 		}
 	}
 	if (match)
 		cout << "Match: BC " << i << "," << j << endl;
 	else
 		cout << "Not-Match: BC " << i << "," << j << endl;
 	return match;
 }

/** Match instance-i of this BC with otherData BC, return boolean. */
 bool BlockCode::matchBC(int i, vector<int> *otherData)
 {
 	bool match = true;
 	for (int k = 0; k < len; ++k) {
 		// compare instances i and otherData, break immediately upon mismatch
 		if ( (*instances[i])[k] != (*otherData)[k] ) {
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
 bool BlockCode::bruteForce(vector<int> *otherData)
 {
    // finally, compare all instances to the original
    for (int i = 0; i < instances.size(); ++i)
    {
        // once find a match, print it, end loop, return true
        bool match = matchBC(i, otherData);
        printBC(i);
        if ( match ) {
            return true;
        }
    }

    // if find none, return false;
    cout << "No match found by bruteForce()" << endl;
    return false;
}

/** Generate all nonredundant BC instances for bruteForce() */
void BlockCode::genAllInstances()
{
    // reset all ops, and clear instances generated
    instances.clear();
    delete flipper;
    sort( (*indexX).begin(), (*indexX).begin() );
    sort( (*indexY).begin(), (*indexY).begin() );

    // generate all flip patterns, i.e. binaries of length X
    genGray(sizeX);

    // try for each flipper = a binary str
    for(auto e : bins) {
        // reassign flipper ptr to next in bin
        flipper = &e;
        // do for each index permutation of X and Y
        do {
            do {
                // record the instance
                makeTData();
            } while (next_permutation( (*indexX).begin(), (*indexX).begin() ));
        } while (next_permutation( (*indexY).begin(), (*indexY).begin() ));
    }
}

/** Generator of Gray code = binary strings of len n, saved to bins. */
void BlockCode::genGray(int n, bool print)
{
    // base case
    if (n <= 0)
        return;

    // start with one-bit pattern
    bins.push_back(vector<int>{0});
    bins.push_back(vector<int>{1});

    // Every iteration of this loop generates 2*i codes from previously
    // generated i codes.

    int i, j;
    for (i = 2; i < (1<<n); i = i<<1)
    {
    // Enter the prviously generated codes again in bins[] in reverse
    // order. Nor bins[] has double number of codes.
        for (j = i-1 ; j >= 0 ; j--)
            bins.push_back(bins[j]);

        // append 0 to the first half
        for (j = 0 ; j < i ; j++)
            bins[j].push_back(0);

        // append 1 to the second half
        for (j = i ; j < 2*i ; j++)
            bins[j].push_back(1);

    }

    // default print=false; option to print the generated Gray code
    if (print)
    {
     // print contents of bins[]
     for (i = 0 ; i < bins.size() ; i++ )
        for (int j = 0; j < bins[i].size(); ++j)
           cout << bins[i][j];
       cout << endl;

   }

}



// void test()
// {
//  	// BlockCode *bc = new BlockCode(4,3);
//  	// BlockCode *bc = new BlockCode(4,3);
//  	// int sample[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
//  	// int *sam = sample;
//     vector<int> *sam = new vector<int>(12,0);
//  	// vector<int> *sam2 = new vector<int>(12,1);
//     BlockCode *bc2 = new BlockCode(4, 3, sam);
//     // bc->printBC(0);
//     bc2->printBC(0);
//     bc2->flip(1);
//     bc2->printOps('F');
//     bc2->swapX(0,1);
//     bc2->printOps('X');
//     bc2->makeTData();
//     bc2->printBC(1);
//  	// bc2->bruteForce(sam2);
//  	// bc->bruteForce(sam);
//  	// cout << sizeof(*bc);
// }

// int main()
// {
//  	// cout << sizeof();
//     test();	

//     return 0;
// }
