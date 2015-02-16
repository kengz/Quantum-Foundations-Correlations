// #include "canon.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Mat
{
public:
	Mat();
	~Mat();
private:
	static int X, Y;
};


void handler()
{
	int X, Y;
	cout << "Input matrix dimension:" << endl;
	cin >> X >> Y;
	cout << "Entered: " << X << " and " << Y << endl;
}

void pullMat()
{
	// istringstream iss;
	string vals = "1010011";
	int k;
	// int *nums[];

	string tmp;
	while (getline(cin, tmp))
	{
		istringstream iss(tmp);
		while(iss >> k)
		{
			cout << k << endl;
		}
	}
}




int main()
{
	cout << "lorem ipsum";
	// handler();
	pullMat();
	return 0;
}