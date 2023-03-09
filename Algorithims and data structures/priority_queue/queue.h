#pragma once
#include <array>
#define MAX_SIZE 100


class KolejkaPriorytetowa
{
    std::array<int, MAX_SIZE> matrix = { 0 };
    int size = 0;
    void heapify_up(int index);
    void heapify_down(int index);
    
    public:
    KolejkaPriorytetowa(){};
    void insert(int x);
    int RemoveRootElem();
    void print();   
    int getRootElem();

};