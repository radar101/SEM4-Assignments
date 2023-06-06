//Credits: Sarthak Dhaytonde

#include <iostream>
using namespace std;


class Node
{
    char data;
    Node *lchild;
    Node *rchild;

public:
    Node();
    Node(char s);
    friend class OBST;
};

Node::Node()
{
    data = ' ';
    lchild = rchild = NULL;
}

Node::Node(char data)
{
    this->data = data;
    lchild = rchild = NULL;
}

class OBST
{
    Node *root;
    float *p;
    float *q;
    char *input;
    double **w;
    double **c;
    double **r;
    int n;

public:
    OBST();
    void getInfo();
    void calculateWeight();
    Node *createTree(int, int);
    void inorder(Node *root);
    void preorder(Node *root);
    void postorder(Node *root);
    void displayMat();
    Node *getroot()
    {
        return root;
    }
};


OBST::OBST()
{
    root = NULL;
    p = q = NULL;
    input = NULL;
    n = 0;
}


void OBST::getInfo()
{
    input = new char[n + 1];
    p = new float[n];
    q = new float[n + 1];
    cout << "\nEnter number of identifiers :-> " << endl;
    cin >> n;
    input[0] = ' ';
    for (int i = 1; i < n + 1; i++)
    {
        cout << "I" << i << ":-> ";
        cin >> input[i];
    }
    cout << "Enter Succesful probability-->\n";
    for (int i = 0; i < n; i++)
    {
        cout << "p" << i << " ";
        cin >> p[i];
    }
    cout << "Enter Unsuccesful probability-->\n";
    for (int i = 0; i < n + 1; i++)
    {
        cout << "q" << i << " ";
        cin >> q[i];
    }
    this->calculateWeight();
}

void OBST::displayMat()
{
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            cout << "(" << w[j][i] << "," << c[j][i] << "," << r[j][i] << ") ";
        }
        cout << endl;
    }
    cout << "\n\nCost:-> " << endl;
}


void OBST::calculateWeight()
{
    w = new double *[n + 1];
    c = new double *[n + 1];
    r = new double *[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        w[i] = new double[n + 1];
        c[i] = new double[n + 1];
        r[i] = new double[n + 1];
    }
    for (int i = 0; i < n; i++)
    {
        w[i][i] = q[i];
        r[i][i] = c[i][i] = 0;
        w[i][i + 1] = q[i] + q[i + 1] + p[i];
        r[i][i + 1] = i + 1;
        c[i][i + 1] = w[i][i + 1];
    }
    w[n][n] = q[n];
    r[n][n] = c[n][n] = 0;
    for (int m = 2; m <= n; m++)
    {
        for (int i = 0; i <= n - m; i++)
        {
            double min = 999;
            int j = i + m;
            int k = 0;
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
            for (int i1 = i + 1; i1 <= j; i1++)
            {
                double sum = c[i][i1 - 1] + c[i1][j];
                if (sum < min)
                {
                    min = sum;
                    k = i1;
                }
            }
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            r[i][j] = k;
        }
    }
    root = createTree(0, n);
};


Node *OBST::createTree(int i, int j)
{
    if (i != j)
    {
        int k = r[i][j];
        Node *nn = new Node(input[k]);
        nn->lchild = createTree(i, k - 1);
        nn->rchild = createTree(k, j);
        return nn;
    }
    else
    {
        return NULL;
    }
}


void OBST::inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->lchild);
        cout << root->data << " ";
        inorder(root->rchild);
    }
}


void OBST::preorder(Node *root)
{
    if (root != NULL)
    {
        cout << root->data << " ";
        preorder(root->lchild);
        preorder(root->rchild);
    }
}


void OBST::postorder(Node *root)
{
    if (root != NULL)
    {
        postorder(root->lchild);
        postorder(root->rchild);
        cout << root->data << " ";
    }
}

int main()
{
    OBST obj;
    obj.getInfo();
    while (true)
    {
        int option, num;
        obj.calculateWeight();
        cout << "\n1.Inorder\n2.Preoder\n3.Postorder\n4.Display Mat\nExit\nChose an option:";
        cin >> option;
        if (option == 1)
        {
            obj.inorder(obj.getroot());
            cout << endl;
        }
        else if (option == 2)
        {
            obj.preorder(obj.getroot());
            cout << endl;
        }
        else if (option == 3)
        {
            obj.postorder(obj.getroot());
            cout << endl;
        }
        else if (option == 4)
        {
            obj.displayMat();
        }
        else
        {
            cout << "\n-----------THANK YOU !!!!----------\n";
            break;
        }
    }
    return 0;
}
