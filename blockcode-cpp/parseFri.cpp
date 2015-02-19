#include "parseFri.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

class bitAdder;
// parse Fripertinger's coefficient rep of BC, generate the corres BC in txt file for use with algorithm
parseFri::parseFri()
{
	// ba=NULL;
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

		// X = (*coef)[0]; Y = (*coef)[1]; Z = (*coef)[2];
		// delete coef;

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

	ifs.open (tar[i], ifstream::app);

	// continue with making BC
}

void parseFri::makeBC()
{
	// assigning the variables for making BC from bitAdder
	X = (*coef)[0]; Y = (*coef)[1]; Z = (*coef)[2];

	// value of coef
	int n;
	bool* b;

	ba = new bitAdder(X);
	ba->genBins();
	int splitY = 0;
	// start iterator from beyond spec (+3 in coef)
	for (auto it = coef->begin()+3; it != coef->end(); ++it)
	{
		if (splitY++ % Y == 0) cout << "Split" << endl;
		cout << "var is " << *it << endl;
		b = ba->getBin(7);
		// for(bool m : *b) {}
		for (int i = 0; i < X; ++i)
		{
			cout << "bool arr" << b[i] << endl;
		}
		// for(bool b : *(ba->getBin(*it)) )
		// 	cout << b << " ";
		// ba->getBin(n);
	}

	
}


void test()
{
	parseFri meh;
	// for (int i = 0; i < 7; ++i)
	// {
	// 	meh.readSrc(i);
	// }
	// ofs << sizeof(meh.src);
	// meh.readSrc(6);
	meh.readSrc(1);
	meh.makeBC();

}

int main()
{
	test();
	return 0;
}