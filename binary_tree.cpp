#include<bits/stdc++.h>
using namespace std;

class Node{
	int data;
	Node *right, *left;
	Node(int data){
		this->data = data;
		this->right = NULL;
		this->left = NULL;
	}
	template<class T>
	friend class Stack;
	template<class T>
	friend class Queue;
	friend class BinTree;
};


template<class T>
class Queue{
    public:
    int size = 200, frontd, reard;
    T *arr;
    Queue(){
        arr = new T[size];
        frontd = -1;
        reard = -1;
    }

    bool empty(){
        if(frontd==-1 or frontd>reard)return true;
        else return false;
    }

    void push(T data){
        if(frontd == -1 and reard == -1){
            frontd++;
        }
        reard++;
        arr[reard] = data;
    }

    void pop(){
        front++;
    }
    
    T front(){
        return arr[frontd];
    }
};




template<class T>
class Stack{
    public:
    int t, sized = 200;
    T *arr;
    Stack(){
        t = -1;
        arr = new T[sized];
    }

    bool isFull(){
        if(t == sized-1) return true;
        else return false;
    }

    bool empty(){
        if(t == -1) return true;
        else return false;
    }
    
    T top(){
        return arr[t];
    }
    
    void push(T node){
        t++;
        arr[t] = node;
    }
    
    void pop(){
        t--;
    }
    
    int size(){
        return t+1;
    }
};

class BinTree{
public:
	Node *root;
	BinTree(){
		root = NULL;
	}

   Node* insertRec(){
        int x;
        cout<<"Enter data (or -1 to exit): "<<endl;
        cin>>x;
        if(x == -1) {
            return nullptr;
        }
        Node* newNode = new Node(x);
        cout<<"Inserting left child of "<<x<<endl;
        newNode->left = insertRec();
        cout<<"Inserting right child of "<<x<<endl;
        newNode->right = insertRec();
        return newNode;
    }   

	void insertIte(int data) {
		if(this->root == NULL){
			this->root = new Node(data);
			return;
		}
	    std::Queue<Node*> q;
	    q.push(this->root);

	    while (!q.empty()) {
	        Node* curr = q.front();
	        q.pop();

	        if (curr->left == NULL) {
	            curr->left = new Node(data);
	            break;
	        } else {
	            q.push(curr->left);
	        }

	        if (curr->right == NULL) {
	            curr->right = new Node(data);
	            break;
	        } else {
	            q.push(curr->right);
	        }
	    }
	}

	void inOrder_rec(Node *root){
		if(root==NULL)return;
		inOrder_rec(root->left);
		cout<<root->data<<" ";
		inOrder_rec(root->right);
	}

	void preOrder_rec(Node *root){
		if(root==NULL) return;
		cout<<root->data<<" ";
		preOrder_rec(root->left);
		preOrder_rec(root->right);
	}

	void postOrder_rec(Node *root){
		if(root==NULL) return;
		postOrder_rec(root->left);
		postOrder_rec(root->right);
		cout<<root->data<<" ";
	}
	
	Stack<Node*> st;

	void inOrder_iterator(){
		Node *cur = this->root;
		while(true){
			while(cur!=NULL){
				st.push(cur);
				cur = cur->left;
			}
			if(st.size()){
				cur = st.top();
				st.pop();
				cout<<cur->data<<" ";
				cur = cur->right;
			}
			else return;		
		}
	}

	void preOrder_iterator(){
		Node *cur = this->root;
		st.push(cur);
		while(!st.empty()){
			Node *node = st.top();
			cout<<node->data<<" ";
			st.pop();
			if(node->right) st.push(node->right);
			if(node->left) st.push(node->left);
		}
	}

	void postorder_iterative() {
	    if (this->root == NULL) {
	        return;
	    }

	    std::stack<Node*> s1, s2;
	    s1.push(this->root);

	    while (!s1.empty()) {
	        Node* curr = s1.top();
	        s1.pop();
	        s2.push(curr);

	        if (curr->left != NULL) {
	            s1.push(curr->left);
	        }						
	        if (curr->right != NULL) {
	            s1.push(curr->right);
	        }
	    }

	    while (!s2.empty()) {
	        std::cout << s2.top() << " ";
	        s2.pop();
	    }
	}

	void mirrorTreeRec(Node *root){
		Node* cur = root;
		if(cur==NULL) return;

		mirrorTreeRec(cur->left);
		mirrorTreeRec(cur->right);
		Node *temp = cur->left;
		cur->left = cur->right;
		cur->right = temp;
	}

	int treeHeightRec(Node *root){
		if(root == NULL) return 0;
		int l = treeHeightRec(root->left);
		int r = treeHeightRec(root->right);
		int maxi= max(l,r) + 1;
		return maxi;
	}

	Node* copyTreeRec(Node *oldRoot, Node *newRoot){
		newRoot = oldRoot;
		return newRoot;
	}

	int countLeaves_recursive(Node *root) {

	    if (root == NULL) {
	        return 0;
	    }
	  
	    if (root->left == NULL && root->right == NULL) {
	        return 1;
	    }
	    
	    int leftLeaves = countLeaves_recursive(root->left);
	    int rightLeaves = countLeaves_recursive(root->right);
	    
	    return leftLeaves + rightLeaves;
	}

	int countLeaves_iterative(Node *root) {

	    if (root == NULL) {
	        return 0;
	    }
	    Queue<Node*> q;
	    q.push(root);
	    int count = 0;
	    while (!q.empty()) {
	        Node* curr = q.front();
	        q.pop();

	        if (curr->left == NULL && curr->right == NULL) {
	            count++;
	        }
	        if (curr->left != NULL) {
	            q.push(curr->left);
	        }
	        if (curr->right != NULL) {
	            q.push(curr->right);
	        }
	    }
    	return count;
	}

	int countNodes_recursive(Node* root) {
	    if (root == NULL) {
	        return 0;
	    }
	    return 1 + countNodes_recursive(root->left) + countNodes_recursive(root->right);
	}

	int countNodes_iterative(Node* root){
		if(root == NULL){
			return 0;
		}
		Queue<Node*> q;
		q.push(root);
		int count = 0;
		while(!q.empty()){
			Node* curr = q.front();
			q.pop();
			if (curr->left != NULL) {
	            q.push(curr->left);
	            count++;
	        }
	        if (curr->right != NULL) {
	            q.push(curr->right);
	            count++;
	        }
		}
		return count+1;
	}

	void eraseAllNodes(){
		this->root = NULL;
		delete this->root;
		return;
	}
};

int main()
{
	BinTree tree, newTree;
	int choice;
	int data,n,a[n];
	Node* searhed;
	char ch = 'y';
	do{
		cout<<"\n\n\n1.Insert Rec\t2.Insert Ite\t3.Inorder Rec\t4.Inorder Ite\t5.Preorder Rec\t6.Preorder Ite\n"
		       "7.Postorder Rec\t8.Postorder Ite\t9.Mirror Tree\t10.Tree copy\t11.Height of tree\t12.Leaves count Rec\n"
		       "13.Leaves count ite\t14.Internal Nodes rec\t15.Internal nodes ite\t16.Erase all nodes"<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Length of the data to be inserted"<<endl;
				cin>>n;
				for(int i=0;i<n;i++){
					cout<<"Enter the data ";
					cin>>a[i];
					tree.root = tree.insertRec();
				}
			break;
			case 2:
				cout<<"Length of the data to be inserted"<<endl;
				cin>>n;
				for(int i=0;i<n;i++){
					cout<<"Enter the data ";
					cin>>a[i];
					tree.insertIte(a[i]);
				}
			break;
			case 3:
				cout<<"Inorder recursive traversal is: "<<endl;
				tree.inOrder_rec(tree.root);
				cout<<endl;
			break;
			case 4:
				cout<<"Inorder iterative traversal is: "<<endl;
				tree.inOrder_iterator();
				cout<<endl;
			break;
			case 5:
				cout<<"Preorder recursive traversal is: "<<endl;
				tree.preOrder_rec(tree.root);
				cout<<endl;
			break;
			case 6:
				cout<<"Preorder iterative traversal is: "<<endl;
				tree.preOrder_iterator();
				cout<<endl;
			break;
			case 7:
				cout<<"Postorder recursive traversal is: "<<endl;
				tree.postOrder_rec(tree.root);
				cout<<endl;
			break;
			case 8:
				cout<<"Postorder iterative traversal is: "<<endl;
				tree.postorder_iterative();
				cout<<endl;
			break;
			case 9:
				tree.mirrorTreeRec(tree.root);
				cout<<"The children are swapped now"<<endl;
			break;
			case 10:
				newTree.root = tree.copyTreeRec(tree.root, newTree.root);
				cout<<"The old tree is copied in the new tree"<<endl;
			break;
			case 11:
				cout<<"The height of the tree is "<<tree.treeHeightRec(tree.root)<<endl;
			break;
			case 12:
				cout<<"The leaves count of tree recursively is "<<tree.countLeaves_recursive(tree.root)<<endl;
			break;
			case 13:
				cout<<"The leaves count of tree iteratively is "<<tree.countLeaves_iterative(tree.root)<<endl;
			break;
			case 14:
				cout<<"The internal nodes count recursively is "<<tree.countNodes_recursive(tree.root)-tree.countLeaves_recursive(tree.root)<<endl;
			break;
			case 15:
				cout<<"The internal nodes count iteratively is "<<tree.countNodes_iterative(tree.root)-tree.countLeaves_iterative(tree.root)<<endl;
			break;
			case 16:
				tree.eraseAllNodes();
				cout<<"The tree nodes are erased"<<endl;
			break;
			default:
			cout<<"Enter valid choice"<<endl;
			break;
		}
		cout<<"\nDo you want to continue(y/n)"<<endl;
		cin>>ch;
	}while(ch == 'y' or ch == 'Y');
}