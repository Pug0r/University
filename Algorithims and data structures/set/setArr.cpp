#include "setArr.h"
#include <iostream>

using namespace std;

bool setArr::checkRangeCorrectness(int x){
	return x >= 0 && x < this->universeSize;
}

setArr::setArr(){table = new bool[universeSize];};

void setArr::insert(int x){
	if (checkRangeCorrectness(x))
		table[x] = true;
}

void setArr::withdraw(int x){
	if (checkRangeCorrectness(x))
		table[x] = false;
}

bool setArr::isInSet(int i){
	if (checkRangeCorrectness(i))
		return table[i];
	return false;
}

int setArr::getSize(){
	int count = 0;
	int i = 0;
	while (i < universeSize){
		if (table[i])
			count++;
		i++;
	}
	return count;
}

void setArr::clearSet(){
	int i = 0;
	while (i < universeSize){
		table[i] = false;
		i++;
	}
}

void setArr::printSet(){
	int i = 0;
	while (i < universeSize){
		if (table[i])
			cout << i << " ";
		i++;
	}
}

setArr setArr::operator+(setArr& object){
	setArr result = setArr();
	int i = 0;
	while (i < universeSize){
		if (table[i] || object.isInSet(i))
			result.insert(i);
		i++;
	}
	return result;
}

setArr setArr::operator*(setArr& object){
	setArr result = setArr();
	int i = 0;
	while (i < universeSize){
		if (table[i] && object.isInSet(i))
			result.insert(i);
		i++;
	}
	return result;
}

setArr setArr::operator-(setArr& object){
	setArr result = setArr();
	int i = 0;
	while (i < universeSize){
		if (table[i] && !(object.isInSet(i)))
			result.insert(i);
		i++;
	}
	return result;
}

bool setArr::operator==(setArr& object){
	int i = 0;
	while (i < universeSize){
		if (!(table[i] == object.isInSet(i)))
			return false;
		i++;
	}
	return true;
}

bool setArr::operator <= (setArr& object){
	int i = 0;
	while (i < universeSize){
		if (table[i] and not object.isInSet(i))
			return false;
		i++;
	}
	return true;
}

