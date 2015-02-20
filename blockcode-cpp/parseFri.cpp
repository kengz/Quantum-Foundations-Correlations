#include "parseFri.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

class bitAdder;
// parse Fripertinger's coefficient rep of BC, generate the corres BC in txt file for use with algorithm
parseFri::parseFri()
{
	src = vector<string> {
		"bc-data/bc2_3_2.txt",
		"bc-data/bc2_3_3.txt",
		"bc-data/bc2_3_4.txt",
		"bc-data/bc2_3_5.txt",
		"bc-data/bc2_3_6.txt",
		"bc-data/bc2_3_7.txt",
		"bc-data/bc2_3_8.txt"
	};
	tar = vector<string> {
		"bc-data/obc2_3_2.txt",
		"bc-data/obc2_3_3.txt",
		"bc-data/obc2_3_4.txt",
		"bc-data/obc2_3_5.txt",
		"bc-data/obc2_3_6.txt",
		"bc-data/obc2_3_7.txt",
		"bc-data/obc2_3_8.txt"
	};

	// init to store Fri's coefficient form
	coef = new vector<int>;
}


void parseFri::readSrc(int i)
{
	// reset coef
	delete coef;
	coef = new vector<int>;
	// int and str variables to parse input
	int tmp;
	string str, token;
	// open up a source file
	ifstream ifs ( src[i] );
	// prepare target file
	ofstream ofs ( tar[i] );

	// error handling
	if (ifs.is_open())
	{
		// Parse BC specs
		// ignore first line
		getline(ifs, str);
		int count = 3;
		// parse next 3 lines of BC spec
		do {
			// take only int
			ifs.ignore(2,'=');
			ifs >> tmp;
			// print to file and save to coef
			ofs << tmp << " ";
			coef->push_back(tmp);
			// clear line
			getline(ifs, str);
			count--;
		} while (count > 0);

		ofs << endl;

		// parse the BC coef, ignoring commas
		do {
			// get next line, make as sstream
			getline(ifs, str);
			stringstream ss(str);
			// split delimited by ','
			while( getline(ss, token, ',') )
			{
				// convert string to int, then save
				tmp = stoi(token);
				coef->push_back(tmp);
			}
		} while (!ifs.eof());
	}

	else ofs << "Unable to open file" << endl;

	// close for now
	ifs.close();
	ofs.close();

	// continue with making BC
}

void parseFri::writeTar(int i)
{
	// assigning the variables for making BC from bitAdder
	X = (*coef)[0]; Y = (*coef)[1]; Z = (*coef)[2];

	bool* binary;
	// prepare the binaries for the coef
	ba = new bitAdder(X);
	ba->genBinaries();
	
	ofstream ofs;
	ofs.open (tar[i], ofstream::app);
	// start iterator from beyond spec (+3 in coef)
	int splitWhen = 0;
	for (auto it = coef->begin()+3; it != coef->end(); ++it)
	{
		// splitter every end of BC
		if (splitWhen++ % Y == 0) ofs << endl;
		// cout << "coef is " << *it << endl;
		// get binary specified by coef and print
		binary = ba->asBinary(*it);
		for (int x = 0; x < X; ++x)
			ofs << binary[x] << " ";
		ofs << endl;
	}

	ofs.close();
}

// run the method to parse and generate BC, formatted to be taken in by canon.cpp
void parseFripertinger()
{
	parseFri fri;
	for (int i = 0; i < 7; ++i)
	{
		fri.readSrc(i);
		fri.writeTar(i);
	}

}



// void test()
// {
// }

// int main()
// {
// 	test();
// 	// parseFripertinger();
// 	return 0;
// }