#pragma once
#include<iostream>
#include <vector>

class setList
{
    std::vector<int> vec;

public:

    setList();
    setList(const setList& l1);
    int getSize();  
    void printSet(); 
    void insert(int x);
    void withdraw(int x);
    bool isInSet(int x); 
    setList operator+(setList& obj);  
    setList operator*(setList& obj);   
    setList operator-(setList& obj);
    bool operator==(setList& obj);  
    bool operator<=(setList& obj);
    
};


