#include <iostream>
#define FAIL_VALUE -997
using namespace std;

struct Node{
	int data;
	Node *next;
};

class pointerQueue{
private:
	Node* head;

public:
	pointerQueue(){head->next = NULL;}

	void push(int element){
		Node *toInsert = new Node; 
		toInsert->data = element;
		if (head->next == NULL)
			head->next = toInsert;
		else{
			Node *iterator = head;
			while(iterator->next != NULL){
				iterator = iterator->next;
			}
			iterator->next = toInsert;
			}
	}	

	int pop(){
		if (head->next == NULL)
			return FAIL_VALUE;
		int temp = head->next->data;
		head->next = head->next->next;
		return temp;
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

