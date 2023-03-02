#include <iostream>
using namespace std;

// autor: Aleksander Pugowski 19.12.2022
// Funkcja umożliwiające printowanie drzewa nie jest mojego autorstwa


struct Node{
	int data;
	Node *right;
	Node *left;
};

class binarySearchTree{
private:
	Node *root;

public:
	binarySearchTree(){root = NULL;}

Node* getRoot(){
	return this->root;
}

int insert(int x){
	if (root == NULL){
		Node *temp = new Node;
		temp->data = x;
		temp->left = NULL;
		temp->right = NULL;
		root = temp;
		return 1;
	}

	Node *toInsert = new Node;
	toInsert->data = x;
	toInsert->right = NULL;
	toInsert->left = NULL;
	Node *iterator = root;
	while(!((iterator->data >= x && iterator->left == NULL) || (iterator->data < x && iterator->right == NULL))){
		if (iterator->data > x)
			iterator = iterator->left;
		else
			iterator = iterator->right;
	} 
	if (iterator->data >= x)
		iterator->left = toInsert;
	else
		iterator->right = toInsert;

	return 1;
}

bool search(int x){
	if (root == NULL)
		return false;
	Node *iterator = root;
	while(!(iterator->right == NULL && iterator->left == NULL)){
		if (iterator->data == x)
			return true;
		// Check if there even is the next node
		if (iterator->data > x && iterator->left == NULL)
			return false;
		if (iterator->data < x && iterator->right == NULL)
			return false;
		if (iterator->data > x)
			iterator = iterator->left;
		else
			iterator = iterator->right;
	}
	if (iterator->data == x)
		return true;
	return false;
}

int DELETE(int x){
	// Basic edge cases
	if (root == NULL)
		return -1;
	if (this->search(x) == false)
		return -1;

	// Deleting the root
	if (root->data == x){
		if (root->left == NULL && root->right == NULL){
			root = NULL;
			return 1;
		}
		if (root->left == NULL && root->right != NULL){
			root = root->right;
			return 1;
		}
		if (root->left != NULL && root->right == NULL){
			root = root->left;
			return 1;
		}
		Node *replacement = root->right;
		Node *replacementParent = root;
		while(!(replacement->left == NULL && replacement->right == NULL)){
			replacementParent = replacement;
			replacement = replacement->left;
		}
		root->data = replacement->data;
		if (replacementParent == root)
			replacementParent->right = NULL;
		else
			replacementParent->left = NULL;
		return 1;		
	}

	// Deleting any other node
	Node *iterator = root;
	while(!((iterator->right != NULL && iterator->right->data == x) || (iterator->left != NULL && iterator->left->data == x))){
		if (iterator->data >= x)
			iterator = iterator->left;
		else
			iterator = iterator->right;
	}
	// the node to delete is on the right
	if (iterator->right != NULL && iterator->right->data == x){
		// No children scenario
		if(iterator->right->left == NULL && iterator->right->right == NULL){
			iterator->right = NULL;
			return 1;
		}
		// One child scenario
		else if(iterator->right->left == NULL && iterator->right->right != NULL){
			iterator->right = iterator->right->right;
			return 1;
		}
		else if(iterator->right->right == NULL && iterator->right->left != NULL){
			iterator->right = iterator->right->left;
			return 1;
		}
		// two children scenario - finding successor in inorder search
		Node *replacement = iterator->right->right;
		Node *replacementParent = iterator->right;
		while(!(replacement->left == NULL && replacement->right == NULL)){
			replacementParent = replacement;
			replacement = replacement->left;
		}
		iterator->right->data = replacement->data;
		if (replacementParent == iterator->right)
			replacementParent->right = NULL;
		else
			replacementParent->left = NULL;
		return 1;
	}

	// the node to delete is on the left - same thing as above 
	else{
		if(iterator->left->left == NULL && iterator->left->right == NULL){
			iterator->left = NULL;
			return 1;
		}
		else if(iterator->left->left == NULL && iterator->left->right != NULL){
			iterator->left = iterator->left->right;
			return 1;
		}
		else if(iterator->left->right == NULL && iterator->left->left != NULL){
			iterator->left = iterator->left->left;
			return 1;
		}
		Node *replacement = iterator->left->right;
		Node *replacementParent = iterator->left;
		while(!(replacement->left == NULL && replacement->right == NULL)){
			replacementParent = replacement;
			replacement = replacement->left;
		}
		iterator->left->data = replacement->data;
		if (replacementParent == iterator->left)
			replacementParent->right = NULL;
		else
			replacementParent->left = NULL;
		return 1;
	}
}
	};


// IT IS NOT MY FUNCTION, I found it on the internet, on some old forum, it visualisies the tree quite nicely - easier to test 
void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        std::cout << node->data<< std::endl;

        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void printBT(const Node* node)
{
    printBT("", node, false);    
}



int main(){
	cout << "Hello World" << endl;
	binarySearchTree a = binarySearchTree();
	cout << "INSERT" << endl;
	a.insert(50);
	a.insert(25);
	a.insert(76);
	a.insert(12);
	a.insert(30);
	a.insert(60);
	a.insert(85);
	a.insert(52);
	a.insert(70);
	printBT(a.getRoot());
	cout << "SEARCH" << endl;
	cout << a.search(52);
	cout << a.search(50);
	cout << a.search(25);
	cout << a.search(0);
	cout << a.search(-100);
	cout << a.search(1929);
	cout << a.search(200) << endl;
	cout << "DELETE LEAF - 52 and 12" << endl;
	a.DELETE(12);
	a.DELETE(52);
	printBT(a.getRoot());
	cout << "DELETE WHEN ONE CHILD - 60" << endl;
	a.DELETE(60);
	printBT(a.getRoot());
	cout << "DELETE WHEN TWO CHILDREN - 76" << endl;
	a.DELETE(76);
	printBT(a.getRoot());
	cout << "DELETE ROOT- 50" << endl;
	a.DELETE(50);
	printBT(a.getRoot());

	}


