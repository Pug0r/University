#include "queue.h"
#include <array>
#include <iostream>

using namespace std;


void KolejkaPriorytetowa::heapify_up(int index)
{
    if (index <= 0)
        return;
    int parent_index = (index-1) / 2;
    if (matrix[index] < matrix[parent_index])
    {
        swap(matrix[index], matrix[parent_index]);
        heapify_up(parent_index);
    }
}

void KolejkaPriorytetowa::heapify_down(int index)
{
    int lchild = 2*index+1;
    int rchild = 2*index+2;
    // in case we got into uninitiated array territory
    if (lchild > size or rchild > size)
        return;
    if ((matrix[index] <= matrix[lchild]) && (matrix[index] <= matrix[rchild]))
        return;
    if (matrix[rchild] < matrix[lchild])
    {
        swap(matrix[rchild], matrix[index]);
        heapify_down(rchild);
    }
    else
    {
        swap(matrix[lchild], matrix[index]);
        heapify_down(lchild);
    }
}

void KolejkaPriorytetowa::insert(int x)
{
    matrix[size] = x;
    size++;
    int parent = (size-2)/2;
    int lchild = 2*(size-1)+1;
    int rchild = 2*(size-1)+2;
    if (matrix[size-1] < matrix[parent])
        heapify_up(size-1);
    else if ((matrix[size-1] > matrix[lchild]) || (matrix[size-1] > matrix[rchild]))
    {
        heapify_down(size-1);
    }
}

int KolejkaPriorytetowa::RemoveRootElem()
{
    swap(matrix[0], matrix[size-1]);
    size--;
    heapify_down(0);
    return matrix[size];
}
void KolejkaPriorytetowa::print()
{
    for (int i = 0; i < size; i++)
    {
        cout << matrix[i] << " ";
    }
}
int KolejkaPriorytetowa::getRootElem(){return matrix[0];}


int main()
{
    KolejkaPriorytetowa test = KolejkaPriorytetowa();
    for (int i = 10; i != 0; i--)
    {
        test.insert(i);
        test.print();
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < 3; i++)
    {
        test.RemoveRootElem();
        test.print();
        cout << endl;
    }

}
