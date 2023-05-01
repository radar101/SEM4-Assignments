#include <iostream>
using namespace std;

class Node
{
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
    friend class Graph;
};

template <class T>
class Queue
{
public:
    int size = 200, frontd, reard;
    T *arr;
    Queue()
    {
        arr = new T[size];
        frontd = -1;
        reard = -1;
    }

    bool empty()
    {
        if (frontd == -1 or frontd > reard)
            return true;
        else
            return false;
    }

    void push(T data)
    {
        if (frontd == -1 and reard == -1)
        {
            frontd++;
        }
        reard++;
        arr[reard] = data;
    }

    void pop()
    {
        frontd++;
    }

    T front()
    {
        return arr[frontd];
    }
};

template <class T>
class Stack
{
public:
    int size = 200, topi;
    T *arr;
    Stack()
    {
        arr = new T[size];
        topi = -1;
    }

    bool empty()
    {
        return topi == -1;
    }

    void push(T data)
    {
        ++topi;
        arr[topi] = data;
    }

    void pop()
    {
        topi--;
    }

    T top()
    {
        return arr[topi];
    }
};

class Graph
{
    Node **adj;
    int numVertices;

public:
    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        adj = new Node *[numVertices + 1];
        for (int i = 1; i <= numVertices; i++)
            adj[i] = NULL;
    }

    void takeEdge(int e, int v)
    {
        Node *node = new Node(e);
        Node *first = adj[v];
        if (first == NULL)
            adj[v] = node;
        else
        {
            while (first->next != NULL)
                first = first->next;
            first->next = node;
        }
        node = new Node(v);
        first = adj[e];
        if (first == NULL)
            adj[e] = node;
        else
        {
            while (first->next != NULL)
                first = first->next;
            first->next = node;
        }
    }
    void printList()
    {
        for (int i = 1; i <= numVertices; i++)
        {
            Node *temp = adj[i];
            cout << i << "->";
            while (temp != NULL)
            {
                cout << temp->data << "->";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    }

    void BFS(int startVertex)
    {
        bool *visited = new bool[numVertices];
        for (int i = 1; i <= numVertices; i++)
        {
            visited[i] = false;
        }

        visited[startVertex] = true;
        Queue<int> q;
        q.push(startVertex);
        while (!q.empty())
        {
            startVertex = q.front();
            q.pop();
            cout << startVertex << " ";
            Node *temp = adj[startVertex];
            while (temp != NULL)
            {
                if (!visited[temp->data])
                {
                    visited[temp->data] = true;
                    q.push(temp->data);
                }
                temp = temp->next;
            }
        }
    }

    void DFS(int startVertex)
    {
        bool *visited = new bool[numVertices];
        for (int i = 1; i <= numVertices; i++)
        {
            visited[i] = false;
        }

        Stack<int> s;
        s.push(startVertex);
        visited[startVertex] = true;

        while (!s.empty())
        {
            int v = s.top();
            cout << v << " ";
            s.pop();

            Node *temp = adj[v];
            while (temp != NULL)
            {
                if (!visited[temp->data])
                {
                    visited[temp->data] = true;
                    s.push(temp->data);
                }
                temp = temp->next;
            }
        }
    }
};

int main()
{
    int n, ch, v, w, startVertex;
    cout << "Enter the number of vertices: ";
    cin >> n;
    Graph g(n);

    do
    {
        cout << "\n\n----- MENU -----\n";
        cout << "1. Add an edge\n";
        cout << "2. Display the adjacency list\n";
        cout << "3. Breadth First Search (BFS)\n";
        cout << "4. Depth First Search (DFS)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter the vertices (v w) to connect: ";
            cin >> v >> w;
            g.takeEdge(v, w);
            break;
        case 2:
            cout << "Adjacency List:\n";
            g.printList();
            break;
        case 3:
            cout << "Enter the starting vertex: ";
            cin >> startVertex;
            cout << "BFS Traversal: ";
            g.BFS(startVertex);
            break;
        case 4:
            cout << "Enter the starting vertex: ";
            cin >> startVertex;
            cout << "DFS Traversal: ";
            g.DFS(startVertex);
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (ch != 5);

    return 0;
}
