#include <bits/stdc++.h>
using namespace std;

class Node
{
    int key, freq;
    Node *right, *left;
    Node(int key, int freq)
    {
        this->key = key;
        this->freq = freq;
        this->right = NULL;
        this->left = NULL;
    }
    friend class OBST;
};

class OBST
{
public:
    Node *root;
    Node **arr;
    int **w;
    int **c;
    int **r;
    int *p;
    int *key;
    int n;

    OBST(int n)
    {
        this->n = n;
        root = NULL;
        arr = new Node *[n];
        w = new int*[n + 1];
        c = new int*[n + 1];
        r = new int*[n + 1];
        p = new int[n];
        key = new int[n];
        for (int i = 0; i <= n; i++) {
            w[i] = new int[n + 1];
            c[i] = new int[n + 1];
            r[i] = new int[n + 1];
        }
    }

    void takeData()
    {
        int keyi, freq;
        Node *temp;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter key and freq: " << endl;
            cin >> keyi >> freq;
            key[i] = keyi;
            p[i] = freq;
            temp = new Node(keyi, freq);
            arr[i] = temp;
        }
    }

    void sortData()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (arr[i]->freq > arr[j]->freq)
                {
                    Node *temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        for(int i=0;i<3;i++)
        {
            obst(arr[i]);
        }
    }

    void displayData()
    {
        for (int i = 0; i < n; i++)
        {
            cout << arr[i]->key << " " << arr[i]->freq << endl;
        }
    }

    void obst(Node* node)
    {
        Node *newNode = node;
        if (root == NULL)
        {
            root = newNode;
            cout << "inserted as root" << endl;
        }
        else
        {
            Node *current = root;
            Node *parent = NULL;
            while (true)
            {
                parent = current;
                if (newNode->key == current->key)
                {
                    break;
                }
                else if(newNode->key < current->key)
                {
                    current = current->left;
                    if (current == NULL)
                    {
                        parent->left = newNode;
                        cout << "insert at left" << endl;
                        break;
                    }
                   
                }else{
                     current = current->right;
                    if (current == NULL)
                    {
                        parent->right = newNode;
                        cout << "insert at right" << endl;
                        break;
                    }
                }
            }
        }
    }

    void constructTables()
    {
        for (int i = 0; i < n; i++)
        {
            w[i][i + 1] = p[i + 1];
            r[i][i + 1] = i + 1;
            c[i][i + 1] = w[i][i + 1];
        }

        for (int m = 2; m <= n; m++)
        {
            for (int i = 0; i < n - m; i++)
            {
                int min = 999;
                int j = i + m;
                int k;
                w[i][j] = w[i][j - 1] + p[j];
                for (int i1 = i + 1; i1 < j; i1++)
                {
                    int sum1 = c[i][i1 - 1] + c[i1][j];
                    if (sum1 < min)
                    {
                        min = sum1;
                        k = i1;
                    }
                }
                c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
                r[i][j] = k + 1;
            }
        }
        for(int i=0;i<=3;i++){
            for(int j=3;j>=0;j--){
                Node *newNode = new Node(key[r[i][j]], 0);
                obst(newNode);
            }
        }
    }

    void inorder(Node *cur)
    {
        if (cur == NULL)
            return;
        inorder(cur->left);
        cout << cur->key << " ";
        inorder(cur->right);
    }

    void preorder(Node *cur)
    {
        if (cur == NULL)
            return;
        cout << cur->key << " ";
        preorder(cur->left);
        preorder(cur->right);
    }
};


int main()
{
    int choice;
    cout << "Enter the number of nodes: ";
    int n;
    cin >> n;
    OBST obj(n);

    do
    {
        cout << "\n--------- MENU ---------\n";
        cout << "1. Take data\n";
        cout << "2. Sort data\n";
        cout << "3. Construct tables\n";
        cout << "4. Inorder and Preorder Traversal\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            obj.takeData();
            break;

        case 2:
            obj.sortData();
            break;

        case 3:
            obj.constructTables();
            break;

        case 4:
            cout << "Inorder Traversal: ";
            obj.inorder(obj.root);
            cout << "\nPreorder Traversal: ";
            obj.preorder(obj.root);
            cout << endl;
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}