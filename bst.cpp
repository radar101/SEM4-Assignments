#include<bits/stdc++.h>
using namespace std;

class Node{
private:
	string word,meaning;
	Node *right, *left;
	Node(string word, string meaning){
		this->right = NULL;
		this->left = NULL;
		this->word = word;
		this->meaning = meaning;
	}
public:
	void giveWord(Node *&node){
		cout<<endl;
		cout<<node->word<<endl;
	}
	friend class BSTree;
};

class BSTree{
public:
	Node *root;
	BSTree(){
		root = NULL;
	}

	void insertNode(string word,string meaning)
	{
		Node *newNode = new Node(word,meaning);
		if(root == NULL){
			root = newNode;
			cout<<"inserted as root"<<endl;
		}else{
			Node *current = root;
			Node *parent = NULL;
			while(true){
				parent = current;
				if(newNode->word < current->word){
					current = current->left;
					if(current == NULL){
						parent->left = newNode;
						cout<<"insert at left"<<endl;
						return;
					}
				}else{
					current = current->right;
					if(current == NULL){
						parent->right = newNode;
						cout<<"insert at right"<<endl;
						return;
					}
				}
			}
		}
		return;
	}

	void updateMeaning(string word, string newMeaning){
		Node* cur = searhed(word);
		cur->meaning = newMeaning;
		return;
	}

	Node* searchNode(string word){
			Node *current = root;
			Node *parent = NULL;
			int count = 0;
			while(current->word!=word){
				parent = current;
				count++;
				if(current!=NULL){
					if(current->word > word){
						current = current->left;
					}else{
						current = current->right;
					}
				}
				if(current == NULL){
					cout<<"keyword is not present"<<endl;
					parent = NULL;
					cout<<"The total no of comparisons made are "<<count<<endl;
					return current;
				}
			}
			cout<<"The keyword is present"<<endl;
			cout<<"The total no of comparisons made are "<<count<<endl;
			return current;
		}

	void deletion(string word){
		Node* parent = NULL;
		Node* current = root;
		while(current->word!=word){
			parent = current;
			if(current!=NULL){
				if(current->word > word){
					current = current->left;
				}else{
					current = current->right;
				}
			}
		}

		if(current == NULL)return;
		if(current->left == NULL and current->right==NULL)
		{
			if(current!=root)
			{
				if(parent->left == current) parent->left = NULL;
				else parent->right = NULL;
			}else root = NULL;
			free(current);
		}
		else if(current->left and current->right)
		{
			Node *succesor = findMinimum(current->right);
			string val = succesor->word;
			deletion(succesor->word);
			current->word = val;

		}else{
			Node* child;
			if(current->left) child = current->left;
			else child = current->right;
			if(current!=root)
			{
				if(current==parent->left)
					parent->left = child;
				else
					parent->right = child;
			}else root = child;
			free(current);

		}
	}

	Node* findMinimum(Node* current)
	{
		while(current->left!=NULL) current = current->left;
		return current;    
	}

	void ascendingOrder(Node *node){
		if(node==NULL)return;
		ascendingOrder(node->left);
		cout<<node->word<<" ";
		ascendingOrder(node->right);
	}

	void descendingOrder(Node *node){
		if(node==NULL)return;
		descendingOrder(node->right);
		cout<<node->word<<" ";
		descendingOrder(node->left);
	}
};


int main()
{
	BSTree tree;
	int choice;
	string word, meaning;
	Node* searhed;
	char ch = 'y';
	do{
		cout<<"\n\n\n1.Insert\t2.Search\t3.Delete\t4.Update meaning\t5.Ascending order\t6.Descending order"<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:
			cout<<"\n\nEnter the word ";
			cin>>word;
			cout<<"\nEnter it's meaning ";
			cin>>meaning;
			tree.insertNode(word, meaning);
			break;
		case 2:
			cout<<"\nEnter the keyword to search ";
			cin>>word;
			searhed = tree.searchNode(word);
			break;
		case 3:
			cout<<"\nEnter the keyword to delete"<<endl;
			cin>
			>word;
			tree.deletion(word);
			cout<<"The word deleted from the dictionary"<<endl;
			break;
		case 4:
			cout<<"Enter the word to update the meaning"<<endl;
			cin>>word;
			cout<<"Enter the new meaning for the word"<<endl;
			cin>>meaning;
			tree.updateMeaning(word,meaning);
			break;
		case 5:
			tree.ascendingOrder(tree.root);
			break;
		case 6:
			tree.descendingOrder(tree.root);
			break;
		default:
			cout<<"Enter valid choice"<<endl;
			break;
		}
		cout<<"\nDo you want to continue(y/n)"<<endl;
		cin>>ch;
	}while(ch == 'y' or ch == 'Y');
}