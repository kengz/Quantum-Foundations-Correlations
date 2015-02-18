#ifndef BITADDER_H
#define BITADDER_H

class bitAdder
{
public:
	bitAdder(int length);
	~bitAdder() {}
	void add();
	void printBin();
	bool* getBin() { return binary; }
private:
	// the position of bit for add(); the length of bit
	int pos, length;
	// the binary string; a pointer to a bit (tis for "this")
	bool *binary, *tis;
};

#endif