#include "setList.h"
#include <iostream>

using namespace std;

setList::setList(){};

setList::setList(const setList& l1){this->vec = l1.vec;}

int setList::getSize(){
	return this->vec.size();
}

void setList::printSet(){
	for (auto i: this->vec)
		cout << i << " ";
}

void setList::insert(int x){
	this->vec.push_back(x);
}

void setList::withdraw(int x){
	for (int i=0; i<this->vec.size(); i++){
		if (vec[i] == x){
			vec.erase(vec.begin() + i);
			return;
		}
	}
	return;
}

bool setList::isInSet(int x){
	for (int i=0; i<this->vec.size(); i++){
		if (vec[i] == x)
			return true;
	}
	return false;
}

setList setList::operator+(setList& obj){
	setList result = obj;
	for (int i=0; i<this->vec.size(); i++){
		if (!(result.isInSet(vec[i])))
			result.insert(vec[i]);
	}
	return result;
}

setList setList::operator*(setList& obj){
	setList result = setList();
	for (int i=0; i<this->vec.size(); i++){
		if (obj.isInSet(vec[i]))
			result.insert(vec[i]);
	}
	return result;
}

setList setList::operator-(setList& obj){
	setList result = setList();
	for (int i=0; i<this->vec.size(); i++){
		if (!(obj.isInSet(vec[i])))
			result.insert(vec[i]);
	}
	return result;
}

bool setList::operator==(setList& obj){
	if (*this<=obj && obj<=*this)
		return true;
	return false;
}

bool setList::operator<=(setList& obj){
	for (int i=0; i<this->vec.size(); i++){
		if (!(obj.isInSet(vec[i])))
			return false;
	}
	return true;
}


