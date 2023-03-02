#include <iostream>
#define FAIL_VALUE -997
using namespace std;


struct Node{
	int data;
	Node *next;
};

class pointerStack{
private:
	Node* head;

public:
	pointerStack(){head->next = NULL;}

	void push(int element){
		Node *toInsert = new Node; 
		toInsert->data = element;
		Node* tmp = head->next;
		head->next = toInsert;
		toInsert->next = tmp;
	}	

	int pop(){
		if (head->next == NULL)
			return FAIL_VALUE;
		int tmp = head->next->data;
		head->next = head->next->next;
		return tmp;
	}

    void show(){
    	Node *iterator = head->next;
        while(iterator->next != NULL){
        	cout << iterator->data << endl;
        	iterator = iterator->next;
        }
        cout << iterator->data << endl;
      	cout << "-----" << endl;
    }
};

