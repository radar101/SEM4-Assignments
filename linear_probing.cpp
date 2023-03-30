#include <bits/stdc++.h>
using namespace std;

class DataItem {
public:
    int telePhone;
    string name;
 
    // Constructor of hashnode
    DataItem(int telePhone, string name)
    {
        this->name = name;
        this->telePhone = telePhone;
    }
};
 
class HashMap {
    DataItem** arr;
    int SIZE;
    DataItem* temp;
 
public:
    HashMap()
    {
        SIZE = 10;
        arr = new DataItem*[SIZE];
        for (int i = 0; i < SIZE; i++)
            arr[i] = NULL;
        temp = new DataItem(-1, " ");
    }

    int hashCode(int key)
    {
        return key % SIZE;
    }
 
    void insertNode(int telePhone, string name)
    {
        DataItem* temp = new DataItem(telePhone, name);
        int hashIndex = hashCode(telePhone);
 
        // find next free space
        while (arr[hashIndex] != NULL
               && arr[hashIndex]->telePhone != telePhone
               && arr[hashIndex]->telePhone != -1) {
            hashIndex++;
            hashIndex %= SIZE;
        }
        arr[hashIndex] = temp;
    }

    string search(int telePhone)
    {
        int hashIndex = hashCode(telePhone);
        int counter = 0;
        while (arr[hashIndex] != NULL) {
            if (arr[hashIndex]->telePhone == telePhone)
                return arr[hashIndex]->name;
            hashIndex++;
            hashIndex %= SIZE;
        }
        return NULL;
    }
    
    void insertWithRep(int telePhone, string name){
        DataItem* temp = new DataItem(telePhone, name);
        int hashIndex = hashCode(telePhone);
        int temp_index = hashIndex;
 
        // find next free space
        while (arr[hashIndex] != NULL
               && arr[hashIndex]->telePhone != telePhone
               && arr[hashIndex]->telePhone != -1) {
            hashIndex++;
            hashIndex %= SIZE;
        }
        string temp_name;
        int temp_telephone;
        if(arr[temp_index] and hashCode(arr[temp_index]->telePhone)!=temp_index){
            temp_name = arr[temp_index]->name;
            temp_telephone = arr[temp_index]->telePhone;
            arr[temp_index] = temp;
            insertNode(temp_telephone, temp_name);
        }else{
            arr[hashIndex] = temp;
        }
    }

    void display()
    {
        for (int i = 0; i < SIZE; i++) {
            if (arr[i] != NULL && arr[i]->telePhone != -1)
                cout << "Telephone = " << arr[i]->telePhone
                     << "  Name = "
                     << arr[i]->name << endl;
        }
    }
};
 
int main() {
    HashMap phoneBook;
    int choice, telePhone;
    string name;

    while (true) {
        cout << "\n-----PHONE BOOK MENU-----\n";
        cout << "1. Add a new contact(without replacement)\n";
        cout << "2. Add a new contack(with replacement)\n";
        cout << "3. Search for a contact\n";
        cout << "4. Display all contacts\n";
        cout << "5. Exit\n";

        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter the telephone number: ";
                cin >> telePhone;
                cout << "Enter the name: ";
                cin >> name;
                phoneBook.insertNode(telePhone, name);
                cout << "\nContact added successfully!\n";
                break;

            case 2:
                cout << "\nEnter the telephone number: ";
                cin >> telePhone;
                cout << "Enter the name: ";
                cin >> name;
                phoneBook.insertWithRep(telePhone, name);
                cout << "\nContact added successfully!\n";
                break;


            case 3:
                cout << "\nEnter the telephone number to search for: ";
                cin >> telePhone;
                name = phoneBook.search(telePhone);
                if (name == "")
                    cout << "Contact not found!\n";
                else
                    cout << "Name: " << name << endl;
                break;

            case 4:
                cout << "\nList of all contacts:\n";
                phoneBook.display();
                break;

            case 5:
                cout << "\nExiting...\n";
                return 0;

            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    }
    return 0;
}
