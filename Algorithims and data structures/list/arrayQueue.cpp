#include <iostream>
#define FAIL_VALUE -997
#define MAX_SIZE 5
using namespace std;



class ArrayQueue{
private:
	const int max_size = MAX_SIZE;
	int head;
	int tail;
	int empty_spot;
	int queue[MAX_SIZE];
public:
	ArrayQueue(){head=0; tail=0; empty_spot=MAX_SIZE;}

	void correct_overflow(){
		if (tail > MAX_SIZE-1 and empty_spot != 0)
			tail = tail % MAX_SIZE;
		if (head > MAX_SIZE-1 and empty_spot != 0)
			head = head % MAX_SIZE;
	}

	int enqueue(int x){
		correct_overflow();
		if (empty_spot == 0){
			cout << "The queue is full" << endl;
			return FAIL_VALUE;
		}

		queue[tail++] = x;
		empty_spot--;
		return 1;
	}

	int dequeue(){
		correct_overflow();
		if (empty_spot == MAX_SIZE){
			cout << "The queue is empty" << endl;
			return FAIL_VALUE;
		}
		empty_spot++;
		return queue[head++];
	}

	void print(){
		correct_overflow();
		int iter = head;
		int distance = MAX_SIZE - empty_spot;
		while (distance != 0){
			iter = iter % MAX_SIZE;
			cout << queue[iter] << endl;
			iter++;
			distance--;
		}
	cout << "---------------" << endl;
	}
};



int main(){
	cout << "Hello World" << endl;
	ArrayQueue a = ArrayQueue();
	a.enqueue(1);
	a.enqueue(2);
	a.enqueue(3);
	a.enqueue(4);
	a.enqueue(5);
	a.print();
	a.dequeue();
	a.dequeue();
	a.dequeue();
	a.print();
	a.enqueue(7);
	a.enqueue(9);
	a.enqueue(10);
	a.print();
	a.dequeue();
	a.dequeue();
	a.dequeue();
	a.print();
	a.enqueue(1);
	a.enqueue(2);
	a.enqueue(3);
	a.enqueue(4);
	a.enqueue(5);
	a.print();
	// dziala elegancko wszystko
	// TODO: posprzataj kod, usun komentarze
	// cout << a.dequeue() << endl;
	// cout << a.dequeue() << endl;
	// a.print();
	}