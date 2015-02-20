#include "canon.h"
#include <iostream>
#include "time.h"


////////////////
// BC methods //
////////////////
/** Turn the primary BC into a BC object, generate all instances by brute force, then run comparison with all other BCs. */
void Canon::runBC(int z = 0, bool compare = false, bool showFail = false)
{
	makePrimeBC(z);
	// countRedundancy();
	if (compare)
		compareBC(z, showFail);
}


/** Create a primary BC object and generate all instanaces of its class. */
void Canon::makePrimeBC(int z = 0)
{
	prime = BlockCode(X, Y, inputBC[z]);
	cout << "The primary BC is: " << endl;
	prime.printBC(0);

	cout << "Generating all BC instances for brute force" << endl << "..." << endl;
	prime.genAllInstances();
}
void Canon::countRedundancy()
{
	int red = prime.countRedundancy();
	cout << "Number of redundant BC instances: " << red << endl;
}
/** Compare all other saved BC to the primary BC object. param true to show fail matches */
void Canon::compareBC(int z = 0, bool showFail = false)
{
	cout << "Comparing all other BCs to primary:" << endl;
	for (int i = 0; i < Z; ++i)
	{
		// compare the z-BC to other BC
		if (i != z)
		{
			cout << "\n==========================\n" << endl;
			printBC(i);
			prime.bruteForce(inputBC[i], showFail);
			cout << "==========================\n" << endl;
		}
		
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
	// parse all of the Z-th BCs specified
	int z = 0;
	while(z < Z) {
		getBC(z);
		z++;
	}
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

	// there will be Z BC's input as 1D array of length X*Y
	inputBC = new int*[Z];
	for (int z = 0; z < Z; z++)
	{
		// one BC of size X*Y
		inputBC[z] = new int[X*Y]();
		// memset(inputBC[z], 0, sizeof(int)*X*Y);
	}
}
void Canon::getBC(int z)
{
	cout << "Enter BlockCode: " << endl;
	int w = 0;
	// parse z-th BC of length X*Y
	while(w < X*Y) {
		// input each term put into z-BC, index w
		cin >> inputBC[z][w];
		w++;
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


int main()
{
	Canon *can = new Canon();
	can->handler();

	// timing
	clock_t time = clock();

	can->runBC(0, true);
	can->runBC(1, true);
	can->runBC(2, true);

	double dif = (double)( clock() - time ) / CLOCKS_PER_SEC ;
	printf ("\nElasped time is %f seconds.", dif );


	// can->makePrimeBC();
	// can->compareBC();
	// can->printBC(0);
	// can->printBC(1);
	// can->printBC(2);

	return 0;
}



