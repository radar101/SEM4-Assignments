#include <iostream>
using namespace std;

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
        front++;
    }

    T front()
    {
        return arr[frontd];
    }

    T rear()
    {
        return arr[reard];
    }
};

class Graph
{
    int n;
int **arr;

public:
    Graph(int n)
    {
        this->n = n + 1;
        arr = new int*[this->n]; 

        for (int i = 0; i < this->n; i++)
        {
            arr[i] = new int[this->n]; 
        }
    }
    
    void takeEdge(int v1, int v2, int w)
    {
        arr[v1][v2] = w;
        arr[v2][v1] = w;
    }

    void printList()
    {
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                cout << i << " " << j << " " << arr[i][j] << endl;
            }
        }
    }

    int primsAlgo()
    {
        bool visited[n];
        for (int i = 0; i < 4; i++)
        {
            visited[i] = false;
        }
        int x = -1, y = -1, min = 200;
        int temp = 0, v = n-1, ans = 0;
        visited[1] = true;
        while (temp <= v - 2)
        {
            for (int i = 1; i <= v; i++)
            {
                if (visited[i])
                {
                    for (int j = 1; j <= v; j++)
                    {
                        if (!visited[j] && arr[i][j])
                        { 
                            if (min > arr[i][j])
                            {
                                min = arr[i][j];
                                x = i;
                                y = j;
                            }
                        }
                    }
                }
            }
            ans += arr[x][y];
            visited[y] = true;
            temp++;
            min = 200;
        }
        return ans;
    }
    

    
};

int main()
{
    int choice;
    int n,e;
    cout<<"Enter the number of the vertices in the graph: "<<endl;
    cin>>n;
    Graph graph(n);

    do {
        cout << "----- MENU -----" << endl;
        cout << "1. Add Edges" << endl;
        cout << "2. Print Graph" << endl;
        cout << "3. Find Minimum Spanning Tree (Prim's Algorithm)" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int v1, v2, weight;
                cout<<"Enter number of the edges: "<<endl;
                cin>>e;
                cout << "Enter the vertices and weight of the edge (v1 v2 weight): ";
                for(int i = 0;i<e;i++)
                {
                    cin >> v1 >> v2 >> weight;
                    graph.takeEdge(v1, v2, weight);
                }
                
                break;
            }
            case 2:
            {
                cout << "Graph:" << endl;
                graph.printList();
                break;
            }
            case 3:
            {
                int minimumSpanningTreeWeight = graph.primsAlgo();
                cout << "Minimum Spanning Tree Weight: " << minimumSpanningTreeWeight << endl;
                break;
            }
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;

    } while (choice != 4);

    return 0;
}


