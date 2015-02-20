#include "bitadder.h"
#include <iostream>
#include <math.h>

using namespace std;

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


// Generate all binaries of length n, and save to vector
bool** bitAdder::genBinaries()
{
	for (int y = 0; y < height; y++)
	{
		// debug: print the current binary
		// printCurrent();
		// store the current binary into allBinaries
		for (int x = 0; x < length; x++)
			allBinaries[y][x] = current[x];
		// increment the curreny binary by 1
		add();
	}
	return allBinaries;
}

// print allBinaries after generation
void bitAdder::printAll()
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < length; ++x)
			cout << allBinaries[y][x] << " ";
		cout << endl;
	}
}

// print the current bit string
void bitAdder::printCurrent()
{
	for (int i = 0; i < length; ++i)
		cout << current[i] << " " ;
	cout << endl;
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



// int main()
// {

// 	bitAdder ba = bitAdder(24);
// 	clock_t time = clock();
// 	ba.genBinaries();
// 	double dif = (double)( clock() - time ) / CLOCKS_PER_SEC ;
// 	printf ("Elasped time is %f seconds.", dif );

	
// 	// ba.printAll();
	

// 	return 0;
// }
