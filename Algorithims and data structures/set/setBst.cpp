#include <iostream>
#include <vector>
using namespace std;


struct Node
{
	int data;
	Node *right;
	Node *left;
};

void show(Node* node)
{
	if (node != nullptr)
    {
		cout << node->data << " ";
		show(node->right);
		show(node->left);
	}
}

class setBst
{
private:
    Node *root;

public:
    setBst(){root = NULL;}

    Node* getRoot()
    {
        return this->root;
    }

    int insert(int x)
    {
        if (root == NULL)
        {
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
        while(!((iterator->data >= x && iterator->left == NULL) || (iterator->data < x && iterator->right == NULL)))
        {
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

    bool isInSet(int x)
    {
        if (root == NULL)
            return false;
        Node *iterator = root;
        while(!(iterator->right == NULL && iterator->left == NULL))
        {
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

    int withdraw(int x)
    {
        // Basic edge cases
        if (root == NULL)
            return -1;
        if (this->isInSet(x) == false)
            return -1;

        // Deleting the root
        if (root->data == x){
            if (root->left == NULL && root->right == NULL)
            {
                root = NULL;
                return 1;
            }
            if (root->left == NULL && root->right != NULL)
            {
                root = root->right;
                return 1;
            }
            if (root->left != NULL && root->right == NULL)
            {
                root = root->left;
                return 1;
            }
            Node *replacement = root->right;
            Node *replacementParent = root;
            while(!(replacement->left == NULL && replacement->right == NULL))
            {
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
        while(!((iterator->right != NULL && iterator->right->data == x) || (iterator->left != NULL && iterator->left->data == x)))
        {
            if (iterator->data >= x)
                iterator = iterator->left;
            else
                iterator = iterator->right;
        }
        // the node to delete is on the right
        if (iterator->right != NULL && iterator->right->data == x)
        {
            // No children scenario
            if(iterator->right->left == NULL && iterator->right->right == NULL)
            {
                iterator->right = NULL;
                return 1;
            }
            // One child scenario
            else if(iterator->right->left == NULL && iterator->right->right != NULL)
            {
                iterator->right = iterator->right->right;
                return 1;
            }
            else if(iterator->right->right == NULL && iterator->right->left != NULL)
            {
                iterator->right = iterator->right->left;
                return 1;
            }
            // two children scenario - finding successor in inorder search
            Node *replacement = iterator->right->right;
            Node *replacementParent = iterator->right;
            while(!(replacement->left == NULL && replacement->right == NULL))
            {
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
            if(iterator->left->left == NULL && iterator->left->right == NULL)
            {
                iterator->left = NULL;
                return 1;
            }
            else if(iterator->left->left == NULL && iterator->left->right != NULL)
            {
                iterator->left = iterator->left->right;
                return 1;
            }
            else if(iterator->left->right == NULL && iterator->left->left != NULL)
            {
                iterator->left = iterator->left->left;
                return 1;
            }
            Node *replacement = iterator->left->right;
            Node *replacementParent = iterator->left;
            while(!(replacement->left == NULL && replacement->right == NULL))
            {
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

    void printSet()
	{
    	show(this->getRoot());
    }

    void nodesToStack(vector<int>& vec, Node* node)
	{
		if (node != nullptr){
			vec.push_back(node->data);
			nodesToStack(vec, node->right);
			nodesToStack(vec, node->left);
		}
	}
    setBst operator+(setBst& obj)
	{
    	vector<int> temp1;
		nodesToStack(temp1, this->getRoot());
	    vector<int> temp2;
		nodesToStack(temp2, obj.getRoot());
		setBst result;
		for (int i=0; i<temp1.size(); i++)
		{
			result.insert(temp1[i]);
		} 
		for (int i=0; i<temp2.size(); i++){
			if (!(result.isInSet(temp2[i])))
				result.insert(temp2[i]);
		}
		return result;
    } 

    setBst operator*(setBst& obj)
	{
    	vector<int> temp;
		nodesToStack(temp, getRoot());
		setBst result = setBst();
		for (int i=0; i<temp.size(); i++)
		{
			if (obj.isInSet(temp[i]))
				result.insert(temp[i]);
		}
		return result;
	} 

    setBst operator-(setBst& obj)
	{
		vector<int> temp;
		nodesToStack(temp, this->getRoot());
		setBst result = setBst();
		for (int i=0; i<temp.size(); i++){
			if (!(obj.isInSet(temp[i])))
				result.insert(temp[i]);
		}
		return result;
	}
    bool operator==(setBst& obj)
	{
		if (*this<=obj && obj<=*this)
			return true;
		return false;
	}  

    bool operator<=(setBst& obj)
	{
		vector<int> temp;
		nodesToStack(temp, this->getRoot());
		for (int i=0; i<temp.size(); i++){temp[i];}
		for (int i=0; i<temp.size(); i++)
		{
			if (!(obj.isInSet(temp[i])))
				return false;
		}
		return true;
	}
	};


int main(){
	setBst a = setBst();
	a.insert(50);
	a.insert(25);
	a.insert(76);
	a.insert(12);
	a.insert(30);
	cout << "\nset a: ";
	a.printSet();
	setBst b = setBst();
	b.insert(50);
	b.insert(85);
	b.insert(52);
	b.insert(70);
	b.insert(30);
	cout << "\nset b: ";
	b.printSet();
	cout << "\nset a+b: ";
	(a+b).printSet();
	cout << "\nset b+a: ";
	(b+a).printSet();
	cout << "\nset a*b: ";
	(a*b).printSet();
	cout << "\nset b*a: ";
	(b*a).printSet();
	cout << "\nset a-b: ";
	(a-b).printSet();
	cout << "\nset b-a: ";
	(b-a).printSet();
	cout << "\nset b<=a: ";
	cout << (b<=a);
	cout << "\nset a<=b: ";
	cout << (a<=b);
	cout << "\nset a==a: ";
	cout << (a==a);
	cout << "\nset a==b: ";
	cout << (a==b);

	}