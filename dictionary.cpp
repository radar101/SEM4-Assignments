#include <iostream>
using namespace std;
class Node
{
    string word;
    string meaning;
    Node *next;

public:
    Node()
    {
        this->word = "";
        this->meaning = "";
        next = NULL;
    }
    Node(string w, string m)
    {
        this->word = w;
        this->meaning = m;
        next = NULL;
    }

    friend class Dictionary;
};

class Dictionary
{
public:
    Node *hashTable[26];
    Dictionary()
    {
        for (int i = 0; i < 26; i++)
            hashTable[i] = NULL;
    }

    int hash(string w)
    {
        return tolower(w[0]) - 97;
    }

    void insert(string word, string meaning)
    {
        int hashIndex = hash(word);
        Node *newnode = new Node(word, meaning);
        if (hashTable[hashIndex] == NULL)
        {
            hashTable[hashIndex] = newnode;
            return;
        }
        Node *temp = hashTable[hashIndex];
        while (temp->next)
            temp = temp->next;
        temp->next = newnode;
    }

    void display()
    {
        for (int i = 0; i < 26; i++)
        {
            Node *temp = hashTable[i];
            cout << char(i + 97) << "-->";
            while (temp)
            {
                cout << temp->word << ": " << temp->meaning << "-->";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void deleteWord(string word)
    {
        int hashIndex = hash(word);
        Node *temp = hashTable[hashIndex];
        if (temp->word == word)
        {
            hashTable[hashIndex] = hashTable[hashIndex]->next;
            return;
        }
        while (temp->next)
        {
            if (temp->next->word == word)
            {
                Node *temp2 = temp->next;
                temp->next = temp2->next;
                delete (temp2);
                return;
            }
            temp = temp->next;
        }
        cout << "Word Not Found in the Dictionary" << endl;
    }

    Node *search(string w)
    {
        int hashIndex = hash(w);
        Node *temp = hashTable[hashIndex];
        while (temp)
        {
            if (temp->word == w)
            {
                cout << temp->word << " : " << temp->meaning << endl;
                return temp;
            }
            temp = temp->next;
        }
        cout << "Word Not Found in the Dictionary" << endl;
        return NULL;
    }
};

int main()
{
    Dictionary obj;

    int choice;
    int flag = 1;
    while (flag)
    {
        cout << "****************MENU****************" << endl;
        cout << "1.Insert\n2.display\n3.search\n4.delete\n5.Exit\n"
             << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string word, meaning;
            cout << "Enter the word to insert: ";
            cin >> word;
            cout << "Enter meaning to insert: ";
            cin >> meaning;
            obj.insert(word, meaning);
            break;
        }
        case 2:
        {
            cout << "The dictionary is: " << endl;
            obj.display();
            break;
        }
        case 3:
        {
            string word;
            cout << "Enter the word to search: ";
            cin >> word;
            obj.search(word);
            break;
        }
        case 4:
        {
            string word;
            cout << "Enter the word to delete: ";
            cin >> word;
            obj.deleteWord(word);
            break;
        }
        case 5:
        {
            flag = 0;
            break;
        }
        }
        cout << "Do you want to continue(1 for yes and 0 for no)" << endl;
        cin >> flag;
    }
    return 0;
}
