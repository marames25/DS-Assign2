#include <bits/stdc++.h>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

struct Node {
    int key;
    Contact contact;
    int height;
    Node* left;
    Node* right;

    Node(int ID, Contact c) {
        key = ID;
        contact = c;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree {
private:
    Node* root = nullptr;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(Node* node) {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotation(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotation(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insertion(Node* node, Node* newNode) {
        if (!node) return newNode;

        if (newNode->key < node->key)
            node->left = insertion(node->left, newNode);
        else if (newNode->key > node->key)
            node->right = insertion(node->right, newNode);
        else {
            cout << "This contact with ID " << newNode->key << " already exists.\n";
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        // Left Left
        if (balance > 1 && newNode->key < node->left->key)
            return rightRotation(node);

        // Right Right
        if (balance < -1 && newNode->key > node->right->key)
            return leftRotation(node);

        // Left Right
        if (balance > 1 && newNode->key > node->left->key) {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // Right Left
        if (balance < -1 && newNode->key < node->right->key) {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    void inorderTraversal(Node* node) {
        if (node) {
            inorderTraversal(node->left);
            cout << "ID: " << node->key
                 << ", Name: " << node->contact.name
                 << ", Phone: " << node->contact.phone
                 << ", Email: " << node->contact.email << endl;
            inorderTraversal(node->right);
        }
    }

    void printTreeStructure(Node* root, int space = 0, int indent = 5) {
        if (!root) return;
    
        space += indent;
    
        printTreeStructure(root->right, space);
    
        cout << setw(space) << root->key << "\n";
    
        printTreeStructure(root->left, space);
    }
    

    Node* search(Node* node, int key) {
        if (!node || node->key == key)
            return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

public:
    void addContact(int ID, const Contact& c) {
        Node* newNode = new Node(ID, c);
        root = insertion(root, newNode);
    }

    void searchContact(int ID) {
        Node* found = search(root, ID);
        if (!found)
            cout << "\nContact not found!\n";
        else {
            cout << "\nContact found:\n";
            cout << "ID: " << found->key << "\nName: " << found->contact.name
                 << "\nPhone: " << found->contact.phone
                 << "\nEmail: " << found->contact.email << endl;
        }
    }

    void listContacts() {
        if (!root) {
            cout << "\nAddress Book is empty\n";
            return;
        }
        cout << "\nContacts in Address Book:\n";
        inorderTraversal(root);
    }

    void showTree() {
        if (!root) {
            cout << "Tree is empty.\n";
            return;
        }
        printTreeStructure(root);
    }
    
};

int main() {
    AVLTree book;
    ifstream file("../input.txt");

    if (!file.is_open()) {
        cout << "Error: Could not open the file\n";
        return 1;
    }

    int op;
    while (file >> op) {
        if (op == 1) {
            int ID;
            Contact c;
            file >> ID;
            file.ignore();
            getline(file, c.name);
            getline(file, c.phone);
            getline(file, c.email);
            book.addContact(ID, c);
        } else if (op == 2) {
            int ID;
            file >> ID;
            book.searchContact(ID);
        } else if (op == 3) {
            book.listContacts();
        } else if (op == 4) {
            book.showTree();
        } else {
            cout << "Invalid operation code: " << op << endl;
        }
    }

    return 0;
}

