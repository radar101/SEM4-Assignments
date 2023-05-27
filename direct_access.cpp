#include <bits/stdc++.h>
using namespace std;

class Hashtable
{
public:
    int addr;
    Hashtable();
} arr[10];

Hashtable ::Hashtable()
{
    for (int i = 0; i < 10; i++)
        arr[i].addr = -1;
}

class Employee : public Hashtable
{
    int id, size = 10;
    string name, salary, exp;

public:
    void addRecord()
    {
        int count, location, index;
        cout << "How many records to add " << endl;
        cin >> count;
        ofstream out;
        out.open("employee.txt", ios::out);
        for (int i = 0; i < count; i++)
        {
            cout << "Enter id " << endl;
            cin >> id;
            cout << "Enter name " << endl;
            cin >> name;
            cout << "Enter salary " << endl;
            cin >> salary;
            cout << "Enter experience " << endl;
            cin >> exp;

            location = out.tellp();
            index = id % size;
            arr[index].addr = location;
            out << id << " " << name << " " << salary << " " << exp << endl;
        }
        out.close();
    }

    void displayRecord()
    {
        char line[40];
        fstream in;
        in.open("employee.txt", ios::in);
        while (!in.eof())
        {
            in.getline(line, 40);
            cout << line << endl;
        }
        in.close();
    }

    void searchRecord()
    {
        char line[40];
        int Id;
        fstream in;
        in.open("employee.txt", ios::in);
        cout << "Enter the ID of the record to search: ";
        cin >> Id;
        int index = Id % size;
        int location = arr[index].addr;

        if (location == -1)
        {
            cout << "Record not found" << endl;
            return;
        }

        in.seekg(location, ios::beg);
        in.getline(line, 40);
        cout << line << endl;
        cout << "Record found" << endl;
    }

    void deleteRecord()
    {
        char line[40];
        int Id;
        fstream in;
        in.open("employee.txt", ios::in);
        cout << "Enter the id of the record to delete: ";
        cin >> Id;
        int index = Id % size;
        int location = arr[index].addr;
        in.seekg(location, ios::beg);
        in.getline(line, 40);
        cout << line << endl;
        cout << "Deleted record" << endl;
        in.close();

        ifstream inFile("employee.txt");
        ofstream outFile("temp.txt");
        while (inFile.getline(line, 40))
        {
            int tempId;
            stringstream ss(line);
            ss >> tempId;
            if (tempId != Id)
                outFile << line << endl;
        }
        inFile.close();
        outFile.close();

        remove("employee.txt");
        rename("temp.txt", "employee.txt");

        cout << "\nRemaining Records:\n";
        ifstream remainingFile("employee.txt");
        while (remainingFile.getline(line, 40))
        {
            cout << "Record: " << line << endl;
        }
        remainingFile.close();
    }
};

int main()
{
    Employee emp;
    int choice;

    do
    {
        cout << "\n********** Menu **********\n";
        cout << "1. Add a Record\n";
        cout << "2. Display Records\n";
        cout << "3. Search a Record\n";
        cout << "4. Delete a Record\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            emp.addRecord();
            break;
        case 2:
            emp.displayRecord();
            break;
        case 3:
            emp.searchRecord();
            break;
        case 4:
            emp.deleteRecord();
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}