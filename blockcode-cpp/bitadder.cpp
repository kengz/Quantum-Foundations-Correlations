#include "bitadder.h"
#include <iostream>
#include <math.h>

/////////////////
// Constructor //
/////////////////
bitAdder::bitAdder(int length)
{
	// dimension variables
	this->length = length;
	height = pow(2, length);
	pos = length; bit = NULL;

	// the current binary string
	current = new bool[length];
	memset(current, 0, sizeof(bool) * length);

	// set of binaries. init 2D array = **allBinaries. memset to false = 0
	allBinaries = new bool*[height];
	for(int i = 0; i < height; ++i) {
		allBinaries[i] = new bool[length];
		memset(allBinaries[i], false, sizeof(bool)*length);
	}
	// delete method, for reference
	// for(int i = 0; i < sizeY; ++i) {
	// 	delete [] allBinaries[i];
	// }
	// delete [] allBinaries;
}

// void bitAdder::test(int y)
// {
// 	// use to copy binary into row y
// 	for (int x = 0; x < length; x++)
// 		allBinaries[y][x] = binary[x];
// 		// cout << allBinaries[y][x];
// 	// printallBinaries
// 	// for (int y = 0; y < height; ++y)
// 	// {
// 	// 	for (int x = 0; x < length; ++x)
// 	// 	{
// 	// 		cout << allBinaries[y][x];
// 	// 	}
// 	// }

// 	// allBinaries[1][2] = 1;
// 	// cout << allBinaries[1][2];
// 	// cout << allBinaries[0][2];
// }

void bitAdder::printAll()
{
	// print allBinaries
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < length; ++x)
			cout << allBinaries[y][x] << " ";
		cout << endl;
	}
}

// Add 1 to bits with carry
void bitAdder::add()
{
	// start from last bit
	pos--;
	// assign bit ptr to bit at pos, add 1
	bit = &(current[pos]);
	*bit ^= true;
	// if result is 0=false, carry and recurse
	if (! *bit) {
		add();
	}
	// till end, restore pos to last for next addition
	else
		pos = length;
}

// print the current bit string
void bitAdder::printCurrent()
{
	for (int i = 0; i < length; ++i)
		cout << current[i] << " " ;
	cout << endl;
}

// Generate all binaries of length n, and save to vector
bool** bitAdder::genBinaries()
{
	for (int y = 0; y < pow(2,length); y++)
	{
		// debug: print the current binary
		printCurrent();
		// store the current binary into allBinaries
		for (int x = 0; x < length; x++)
			allBinaries[y][x] = current[x];
		// increment the curreny binary by 1
		add();
	}
	return allBinaries;
}



int main()
{
	// int sizeX = 3, sizeY = 8;
	// for(int i = 0; i < sizeY; ++i) {
	// 	delete [] ary[i];
	// }
	// delete [] ary;

	// int** ary = new int*[sizeY];
	// for(int i = 0; i < sizeY; ++i)
	// 	ary[i] = new int[sizeX];
	// cout << ary[1][2];


	// memset(ary, 1, sizeof(ary[0][0]) * 8 * 3);
	// for (int i = 0; i < sizeof(ary); ++i)
	// {
	// 	cout << ary[i];
	// }
	// arr = new bool*[sizeY];

	// int ary[]
	// bool *tmp;
	// tmp = new bool[ sizeof(bool) * sizeX * sizeY ];
	// // bool arr[8][2];
	// memset(tmp, false, sizeof(tmp[0]) * 8 * 3);
	// // tmp = &arr[0][0];
	// for (int i = 0; i < 4; ++i)
	// {
	// 	// (*tmp) [i][1] = -1;
	// }
	// for (int i = 0; i < sizeof(arr); ++i)
	// {
		// cout << tmp[i];
	// }
	bitAdder ba = bitAdder(3);
	// ba.test();
	ba.genBinaries();
	ba.printAll();
	// for (int i = 0; i < 8; ++i)
	// {
	// 	bool* b = ba.getBin(1);
	// 	cout << b[0] << b[1] << b[2] << endl;
	// }
	

	return 0;
}
