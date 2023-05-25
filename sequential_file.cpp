#include <iostream>
#include <fstream>
using namespace std;

class Student {
private:
    int roll;
    string name, div, address;
    fstream Myfile;
    char buffer[40];

public:
    void create() {
        Myfile.open("demo.txt", ios::out);
        if (Myfile) {
            char choice;
            do {
                Student s;
                cout << "Enter Roll Number: ";
                cin >> s.roll;
                cout << "Enter Name: ";
                cin>> s.name;
                cout << "Enter Division: ";
                cin >> s.div;
                cout << "Enter Address: ";
                cin >> s.address;
                Myfile.write((char*)&s, sizeof(s));

                cout << "Do you want to add another record? (y/n): ";
                cin >> choice;
            } while (choice == 'y' || choice == 'Y');
        }
        else {
            cout << "Error while creating file" << endl;
        }
        Myfile.close();
    }

    void display() {
        Myfile.open("demo.txt", ios::in);
        if (Myfile) {
            Student s;
            Myfile.read((char*)&s, sizeof(s));
            while (Myfile) {
                cout << s.roll << " " << s.name << " " << s.div << " " << s.address << endl;
                Myfile.read((char*)&s, sizeof(s));
            }
        }
        else {
            cout << "Error while creating file" << endl;
        }
        Myfile.close();
    }

    void display(int roll) {
        Myfile.open("demo.txt", ios::in);
        if (Myfile) {
            Student s;
            Myfile.read((char*)&s, sizeof(s));
            while (Myfile) {
                if (s.roll == roll) {
                    cout << s.roll << " " << s.name << " " << s.div << " " << s.address << endl;
                    break;
                }
                Myfile.read((char*)&s, sizeof(s));
            }
        }
        else {
            cout << "Error while creating file" << endl;
        }
        Myfile.close();
    }

    void deletion(int roll) {
        Myfile.open("demo.txt", ios::in);
        fstream outfile;
        outfile.open("new.txt", ios::out);
        if (Myfile && outfile) {
            Student s;
            bool isFound = false;
            while (Myfile.read((char*)&s, sizeof(s))) {
                if (s.roll == roll) {
                    cout << "Record deleted:" << endl;
                    cout << s.roll << " " << s.name << " " << s.div << " " << s.address << endl;
                    isFound = true;
                }
                else {
                    outfile.write((char*)&s, sizeof(s));
                }
            }
            if (!isFound) {
                cout << "Record not found with roll number " << roll << endl;
            }
            else {
                cout << "Deletion completed!" << endl;
            }
        }
        else {
            cout << "Error while creating file" << endl;
        }
        Myfile.close();
        outfile.close();
        remove("demo.txt");
        rename("new.txt", "demo.txt");
    }
};

int main() {
    Student s;
    int choice, roll;
    do {
        cout << "------ Menu ------" << endl;
        cout << "1. Create File and Add Records" << endl;
        cout << "2. Display All Records" << endl;
        cout << "3. Display Record by Roll Number" << endl;
        cout << "4. Delete Record by Roll Number" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s.create();
                break;
            case 2:
                s.display();
                break;
            case 3:
                cout << "Enter Roll Number: ";
                cin >> roll;
                s.display(roll);
                break;
            case 4:
                cout << "Enter Roll Number: ";
                cin >> roll;
                s.deletion(roll);
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 5);

    return 0;
}
