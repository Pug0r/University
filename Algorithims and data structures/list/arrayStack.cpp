#include <iostream>
#define FAIL_VALUE -997
#define MAX_SIZE 100
using namespace std;

class ArrayStack{
private:
	const int max_size = MAX_SIZE;
	int cur_elem;
	int stack[MAX_SIZE];

public:
	ArrayStack(){cur_elem = 0;}


	int push(int x){
		if (cur_elem-1 > max_size)
			return FAIL_VALUE;
		stack[cur_elem++] = x;
		return 1;
	}	

	int pop(){
		if (cur_elem == 0)
			return FAIL_VALUE;
		return stack[--cur_elem];

	}

	void print(){
		for(int i=0; i < cur_elem; i++){
			cout << stack[i] << endl; 
		}
	}

};



