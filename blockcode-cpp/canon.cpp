#include "canon.h"
#include <iostream>

////////////////
// BC methods //
////////////////
/** Turn the primary BC into a BC object, generate all instances by brute force, then run comparison with all other BCs. */
void Canon::runBC()
{
	makePrimeBC();
	compareBC();
}

/** Create a primary BC object and generate all instanaces of its class. */
void Canon::makePrimeBC()
{
	// cout << inputBC[0];
	// int *ptr = inputBC[0];
	prime = BlockCode(X, Y, inputBC[0]);
	// prime = BlockCode(X, Y, inputBC[0]);
	cout << "The primary BC is: " << endl;
	// prime.printBC(0);

	cout << "Generating all BC instances for brute force" << endl << "..." << endl;
	// prime.genAllInstances();
	cout << "Instances generated." << endl << endl;
}
/** Compare all other saved BC to the primary BC object. */
void Canon::compareBC()
{
	cout << "Comparing all other BCs to primary:" << endl;
	for (int i = 1; i < Y; ++i)
	{
		cout << "\n==========================\n" << endl;
		printBC(i);
		prime.bruteForce(inputBC[i]);
		cout << "==========================\n" << endl;
	}
}
/** Print a saved BC in proper format. */
void Canon::printBC(int which)
{
	cout << "Running for BC " << which << ":" << endl;
	// format BC
	int i = 0;
	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			// get this instance, access each entry i
			cout << inputBC[which][i] << " ";
			i++;
		}
		cout << endl;
	}
	cout << endl;
	cout << "=Matching with primary BC:=" << endl << endl;	
}


////////////////
// IO Handler //
////////////////
void Canon::handler()
{
	menu();
	getDim();
	// index for next data set, read vertical y
	int y = 0;
	while(y < Z) {
		getBC(y);
		y++;
	}

	cout << inputBC[0];
	cout << inputBC[0][0];
	cout << inputBC[0][1];
	cout << inputBC[0][2];
}

void Canon::menu()
{
	cout 
	<< "\n=================================================================\n" << endl
	<< "Binary BlockCode Classification by Wah Loon Keng.\n" << endl
	<< "This program compares if some BlockCodes(BCs) are equivalent." << endl
	<< "Enter the primary BlockCode, then the other BCs to compare to it." << endl
	<< "\n=================================================================\n" << endl;
}
void Canon::getDim()
{
	cout << "Enter the BC dimension (width height): " << endl;
	cin >> X >> Y;
	cout << "Entered: " << X << " and " << Y << endl;
	cout << "Total number of BCs: " << endl;
	cin >> Z;
	cout << "Entered: " << Z << endl;

	// init inputBC (change name to data set)
	inputBC = new int*[Y];
	for (int y = 0; y < Y; ++y)
	{
		inputBC[y] = new int[X];
		memset(inputBC[y], 0, sizeof(int)*y);
	}
}
void Canon::getBC(int y)
{
	
	cout << "Enter BlockCode: " << endl;
	int z = 0;
	while(z < X*Y) {
		cin >> inputBC[y][z];
		z++;
	}
	cout << "==========================\n" << endl;
}




// void test()
// {
// 	// int** inputBC = new int*[8];
// 	// for (int i = 0; i < 8; ++i)
// 	// {
// 	// 	inputBC[i] = new int[3];
// 	// 	memset(inputBC[i], 0, sizeof(int)*3);
// 	// }
// 	// cout << "size after memset: " << sizeof(inputBC) << endl;
// }





// int main()
// {
// 	test();
// 	// Canon *can = new Canon();
// 	// can->handler();
// 	// can->makePrimeBC();
// 	// can->printBC(0);
// 	// can->printBC(1);
// 	// can->printBC(2);
// 	// can->runBC();

// 	return 0;
// }



