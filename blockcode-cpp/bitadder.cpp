#include "bitadder.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

/////////////////
// Constructor //
/////////////////
bitAdder::bitAdder(int length)
{
	this->length = length;
	pos = length;
	binary = NULL, tis = NULL;
	binary = new bool[length];
	memset(binary, 0, sizeof(bool) * length);
}

// Add 1 to bits with carry
void bitAdder::add()
{
	// start from last bit
	pos--;
	// assign tis ptr to bit at pos, add 1
	tis = &(binary[pos]);
	*tis ^= true;
	// if result is 0=false, carry and recurse
	if (! *tis) {
		add();
	}
	// till end, restore pos to last for next addition
	else
		pos = length;
}

// print the current bit string
void bitAdder::printBin()
{
	for (int i = 0; i < length; ++i)
		cout << binary[i] << " " ;
	cout << endl;
}

// Generate all instances of bit string, length n, and save to vector
vector<bool*>* genBin(int len)
{
	vector<bool*> *store = new vector<bool*>;
	bitAdder ba = bitAdder(len);

	for (int i = 0; i < pow(2,len); ++i)
	{
		// ba.printBin();
		// store a generated bin string
		store->push_back(ba.getBin());
		ba.add();
	}

	return store;
}


int main()
{
	genBin(3);

	return 0;
}
