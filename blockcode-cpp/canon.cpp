#include "canon.h"
#include <iostream>
#include <vector>


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
	prime = new BlockCode(X, Y, vecBC[0]);
	cout << "The primary BC is: " << endl;
	prime->printBC(0);

	cout << "Generating all BC instances for brute force" << endl << "..." << endl;
	prime->genAllInstances();
	cout << "Instances generated." << endl << endl;
}
/** Compare all other saved BC to the primary BC object. */
void Canon::compareBC()
{
	cout << "Comparing all other BCs to primary:" << endl;
	for (int i = 1; i < vecBC.size(); ++i)
	{
		cout << "\n==========================\n" << endl;
		printBC(i);
		prime->bruteForce(vecBC[i]);
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
			cout << (*vecBC[which])[i] << " ";
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
	while(Z > 0) {
		vecBC.push_back(getBC());
		Z--;
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
}
vector<int>* Canon::getBC()
{
	cout << "Enter BlockCode: " << endl;
	vector<int> *arr = new vector<int>;
	int z = X*Y, t;
	while(z > 0) {
		z--;
		cin >> t;
		arr->push_back(t);
	}
	cout << "==========================\n" << endl;

	return arr;
}




int main()
{
	Canon *can = new Canon();
	can->handler();
	can->runBC();

	return 0;
}



