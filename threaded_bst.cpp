//============================================================================
// Name        : threaded_bin_tree.cpp
// Author      : Darshan Mahajan 21247
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

class Node{

    int data;
    Node *right, *left;
    bool rThread, lThread;
    Node(int data){
        this->data = data;
        this->right = NULL;
        this->left = NULL;
        this->rThread = false;
        this->lThread = false;
    }
    friend class TBTree;
};

class TBTree{
public:
    // The root of the Threaded binary tree
    Node* root;

    // Function to insert the node in the TBT
    void create(int data){
        Node* ptr = this->root;
        Node* parent = NULL;

        // Loop to search for the Node with given value and keeping track of the parent
        while(ptr!=NULL){
            if(ptr->data == data){
                cout<<"The data already exist"<<endl;
                return;
            }

            
            if(data < ptr->data){
                parent = ptr;
                if(ptr->lThread == false) ptr = ptr->left;
                else break;
            }

            if(data > ptr->data){
                parent = ptr;
                if(ptr->rThread == false) ptr = ptr->right;
                else break;
            }
        }

        // Creation of the node with given data
        Node* newNode = new Node(data);
        newNode->lThread = true;
        newNode->rThread = true;

        // Insertion as the root node
        if(parent == NULL){
            root = newNode;
//          cout<<"inserted root"<<endl;
        }else if(parent->data > data){          // Insertion as the left node
            newNode->left = parent->left;
            newNode->right = parent;
            parent->lThread = false;
            parent->left = newNode;
//          cout<<"inserted left"<<endl;
        }else if(parent->data < data){          // Insertion as the right node
            newNode->right = parent->right;
            newNode->left = parent;
            parent->rThread = false;
            parent->right = newNode;
//          cout<<"inserted right"<<endl;
        }
    }

    Node* inorderSuccesor(Node* ptr){
        if(ptr->rThread == true)
            return ptr->right;
        ptr = ptr->right;
        while(ptr->lThread == false)
            ptr = ptr->left;
        return ptr;
    }

    Node* inorderPredecessor(Node* ptr){
        if(ptr->lThread == true)
            return ptr->left;
        ptr = ptr->left;
        while(ptr->rThread == false)
            ptr = ptr->right;
        return ptr;
    }

    void inorder(Node* root){
        if(root == NULL){
            cout<<"Tree is empty"<<endl;
            return;
        }
        Node* ptr = root;
        while(ptr->lThread == false)
            ptr = ptr->left;
        while(ptr!=NULL){
            cout<<ptr->data<<" ";
            ptr = inorderSuccesor(ptr);
        }
    }

    void preorder(Node* root){
        Node* ptr = root;
        if(root == NULL){
            cout<<"Tree is empty"<<endl;
            return;
        }
        ptr = root;
        while(ptr!=NULL){
            cout<<ptr->data<<" ";
            if(ptr->lThread == false) ptr = ptr->left;
            else if(ptr->rThread == false) ptr = ptr->right;
            else{
                while(ptr!=NULL and ptr->rThread == true) ptr = ptr->right;
                if(ptr != NULL) ptr = ptr->right;
            }
        }
    }

    void deletion(int toDel){
        Node *ptr = this->root, *par = NULL;
        bool found = false;
        while(ptr!=NULL){
            if(ptr->data == toDel){
                found = true;
                break;
            }

            if(toDel < ptr->data){
                par = ptr;
                if(ptr->lThread == false) ptr = ptr->left;
                else break;
            }

            if(toDel > ptr->data){
                par = ptr;
                if(ptr->rThread == false) ptr = ptr->right;
                else break;
            }
        }

        if(found == false){
            cout<<"The data is not present."<<endl;
            return;
        }

        Node* suc = inorderSuccesor(ptr);
        Node* pre = inorderPredecessor(ptr);

        if(ptr->lThread == true and ptr->rThread == true){
            if(ptr == par->left){
                par->lThread = true;
                par->left = ptr->left;
            }else{
                par->rThread = true;
                par->right = ptr->right;
            }
            ptr = NULL;
            delete ptr;
        }else if(ptr->lThread == true or ptr->rThread == true){
            Node *child;
            if (ptr->lThread)
                child = ptr->right;
            else
                child = ptr->left;
            if (ptr != root) {
                if (ptr == par->left){
                    par->left = child;
                    pre->right = suc;
                }
                else{
                    par->right = child;
                    suc->left = pre;
                }
            }else
                root = child;
            delete ptr;
        }else if(ptr->lThread == false and ptr->rThread == false){
            Node *succesor = inorderSuccesor(ptr->right);
            int val = succesor->data;
            deletion(succesor->data);
            ptr->data = val;
        }
    }
};

int main() {
    TBTree tree;
    int choice, value;
    do {
        cout << "\n1. Insert element in the threaded binary tree";
        cout << "\n2. Inorder traversal";
        cout << "\n3. Preorder traversal";
        cout << "\n4. Delete a node from the threaded binary tree";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                tree.create(value);
                break;
            case 2:
                cout << "Inorder traversal: ";
                tree.inorder(tree.root);
                cout << endl;
                break;
            case 3:
                cout << "Preorder traversal: ";
                tree.preorder(tree.root);
                cout << endl;
                break;
            case 4:
                cout << "Enter the value to delete: ";
                cin >> value;
                tree.deletion(value);
                break;
            case 5:
                cout << "Exiting program...";
                break;
            default:
                cout << "Invalid choice. Please try again.";
                break;
        }
    } while (choice != 5);
    return 0;
}