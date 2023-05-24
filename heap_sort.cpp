#include <iostream>
using namespace std;

void heapifyMin(int a[], int i, int n)
{
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] < a[smallest])
        smallest = l;
    if (r < n && a[r] < a[smallest])
        smallest = r;
    if (smallest != i)
    {
        int temp = a[i];
        a[i] = a[smallest];
        a[smallest] = temp;
        heapifyMin(a, smallest, n);
    }
}

void heapifyMax(int a[], int i, int n)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[largest])
        largest = l;
    if (r < n && a[r] > a[largest])
        largest = r;
    if (largest != i)
    {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        heapifyMax(a, largest, n);
    }
}

void minHeapSort(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMin(a, i, n);

    for (int i = n - 1; i > 0; i--)
    {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapifyMin(a, 0, i);
    }
}

void maxHeapSort(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMax(a, i, n);

    for (int i = n - 1; i > 0; i--)
    {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapifyMax(a, 0, i);
    }
}

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    int choice;
    int n;
    cout<<"Enter the size of an array"<<endl;
    cin>>n;
    int a[n];
    cout<<"Enter data "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    do {
        cout << "----- MENU -----" << endl;
        cout << "1. Min Heap Sort" << endl;
        cout << "2. Max Heap Sort" << endl;
        cout << "3. Print Array" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                minHeapSort(a, n);
                cout << "Array sorted using Min Heap Sort." << endl;
                break;
            }
            case 2:
            {
                maxHeapSort(a, n);
                cout << "Array sorted using Max Heap Sort." << endl;
                break;
            }
            case 3:
            {
                cout << "Array: ";
                printArray(a, n);
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

