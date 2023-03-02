#pragma once
#include <iostream>
class setArr
{
int size;
const int universeSize = 100;
bool* table;
bool checkRangeCorrectness(int x);
public:
	setArr();
	void insert(int x);
	void withdraw(int x);
	bool isInSet(int i);
	int getSize();
	void clearSet();
	void printSet();
	setArr operator+(setArr& object);
	setArr operator*(setArr& object);
	setArr operator-(setArr& object);
	bool operator==(setArr& object);
	bool operator <= (setArr& object);
};

