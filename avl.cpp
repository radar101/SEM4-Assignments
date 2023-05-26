#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string word;
    string meaning;
    int height;
    Node* left;
    Node* right;

    Node(string word, string meaning) {
        this->word = word;
        this->meaning = meaning;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
public:
    Node* root;

    AVLTree() {
        root = NULL;
    }

    int getHeight(Node* node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int getBalanceFactor(Node* node) {
        if (node == NULL)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return y;
    }

    Node* insert(Node* node, string word, string meaning) {
        if (node == NULL)
            return new Node(word, meaning);

        if (word < node->word)
            node->left = insert(node->left, word, meaning);
        else if (word > node->word)
            node->right = insert(node->right, word, meaning);
        else {
            node->meaning = meaning;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        // Left Left
        if (balanceFactor > 1 && word < node->left->word)
            return rightRotate(node);

        // Right Right
        if (balanceFactor < -1 && word > node->right->word)
            return leftRotate(node);

        // Left Right
        if (balanceFactor > 1 && word > node->left->word) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balanceFactor < -1 && word < node->right->word) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* successor(Node* node) {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    Node* deleteEntry(Node* node, string word) {
        if (node == NULL)
            return node;

        if (word < node->word)
            node->left = deleteEntry(node->left, word);
        else if (word > node->word)
            node->right = deleteEntry(node->right, word);
        else {
            // word found ----> Delete the node
            if (node->left == NULL || node->right == NULL) {
                Node* temp = node->left ? node->left : node->right;

                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                } else {
                    *node = *temp;
                }

                delete temp;
            } else {
                Node* temp = successor(node->right);
                node->word = temp->word;
                node->meaning = temp->meaning;
                node->right = deleteEntry(node->right, temp->word);
            }
        }

        if (node == NULL)
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        // Left Left
        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);

        // Left Right
        if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Right
        if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);

        // Right Left
        if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* search(Node* node, string word) {
        if (node == NULL || node->word == word)
            return node;

        if (word < node->word)
            return search(node->left, word);

        return search(node->right, word);
    }

    void inorder(Node* node) {
        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->word << ": " << node->meaning << endl;
        inorder(node->right);
    }

    void descendingOrder(Node* node) {
        if (node == NULL)
            return;

        descendingOrder(node->right);
        cout << node->word << ": " << node->meaning << endl;
        descendingOrder(node->left);
    }

    int getMaxComparisons(Node* node, string word, int comparisons) {
        if (node == NULL)
            return comparisons;

        if (word == node->word)
            return comparisons + 1;

        if (word < node->word)
            return getMaxComparisons(node->left, word, comparisons + 1);

        return getMaxComparisons(node->right, word, comparisons + 1);
    }

    void addEntry(string word, string meaning) {
        root = insert(root, word, meaning);
        cout << "Word added successfully!" << endl;
    }

    void updateMeaning(string word, string newMeaning) {
        Node* node = search(root, word);
        if (node != NULL) {
            node->meaning = newMeaning;
            cout << "Meaning updated." << endl;
        } else {
            cout << "Word not found!" << endl;
        }
    }
};

int main() {
    AVLTree dictionary;
    int choice, comp;
    string word, meaning;

    do {
        cout << "\n------ Dictionary Menu ------" << endl;
        cout << "1. Add a word" << endl;
        cout << "2. Delete a word" << endl;
        cout << "3. Update meaning" << endl;
        cout << "4. Display words in ascending order" << endl;
        cout << "5. Display words in descending order" << endl;
        cout << "6. Get maximum comparisons for a word" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dictionary.addEntry(word, meaning);
                break;
            case 2:
                cout << "Enter word: ";
                cin >> word;
                dictionary.root = dictionary.deleteEntry(dictionary.root, word);
                break;
            case 3:
                cout << "Enter word: ";
                cin >> word;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dictionary.updateMeaning(word, meaning);
                break;
            case 4:
                dictionary.inorder(dictionary.root);
                break;
            case 5:
                dictionary.descendingOrder(dictionary.root);
                break;
            case 6:
                cout << "Enter word: ";
                cin >> word;
                comp = dictionary.getMaxComparisons(dictionary.root, word, 0);
                cout << "Maximum comparisons required: " << comp << endl;
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}