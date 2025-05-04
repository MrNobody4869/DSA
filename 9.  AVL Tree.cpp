#include <iostream>
#include <string>
using namespace std;

// Node structure for AVL Tree
struct Node {
    string key;          // keyword
    string meaning;      // meaning of the keyword
    Node* left;          // pointer to left child
    Node* right;         // pointer to right child
    int height;          // height of the node
};

// Utility function to get the height of a node
int height(Node* n) {
    return n ? n->height : 0;  // Return 0 if null, else height
}

// Utility to get max of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new node
Node* createNode(string key, string meaning) {
    Node* node = new Node();    // Allocate memory
    node->key = key;            // Set keyword
    node->meaning = meaning;    // Set meaning
    node->left = node->right = nullptr;  // Initialize children
    node->height = 1;           // Height of a new node is 1
    return node;
}

// Get balance factor of node
int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; // New root
}

// Left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; // New root
}

// Insert a key into the AVL tree
Node* insert(Node* node, string key, string meaning) {
    if (!node) return createNode(key, meaning); // Base case

    if (key < node->key)
        node->left = insert(node->left, key, meaning);  // Go left
    else if (key > node->key)
        node->right = insert(node->right, key, meaning); // Go right
    else {
        node->meaning = meaning; // Update existing key's meaning
        return node;
    }

    // Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Check balance
    int balance = getBalance(node);

    // Perform rotations
    if (balance > 1 && key < node->left->key)  // Left Left
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)  // Right Right
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {  // Left Right
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {  // Right Left
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Return unchanged node
}

// Display in ascending order (in-order traversal)
void displayAscending(Node* root) {
    if (root) {
        displayAscending(root->left);
        cout << root->key << " : " << root->meaning << endl;
        displayAscending(root->right);
    }
}

// Display in descending order (reverse in-order traversal)
void displayDescending(Node* root) {
    if (root) {
        displayDescending(root->right);
        cout << root->key << " : " << root->meaning << endl;
        displayDescending(root->left);
    }
}

// Search for a keyword and count comparisons
void search(Node* root, string key, int& comparisons) {
    if (!root) {
        cout << "Keyword not found.\n";
        return;
    }
    comparisons++; // Increment comparison count

    if (key == root->key) {
        cout << "Meaning: " << root->meaning << endl;
        cout << "Comparisons: " << comparisons << endl;
    } else if (key < root->key) {
        search(root->left, key, comparisons);
    } else {
        search(root->right, key, comparisons);
    }
}

// Main function - menu driven
int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    do {
        cout << "\n--- AVL Tree Dictionary ---\n";
        cout << "1. Add/Update Keyword\n";
        cout << "2. Display Ascending\n";
        cout << "3. Display Descending\n";
        cout << "4. Search Keyword\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                root = insert(root, key, meaning);
                break;

            case 2:
                cout << "\nDictionary (Ascending Order):\n";
                displayAscending(root);
                break;

            case 3:
                cout << "\nDictionary (Descending Order):\n";
                displayDescending(root);
                break;

            case 4: {
                cout << "Enter keyword to search: ";
                cin >> key;
                int comparisons = 0;
                search(root, key, comparisons);
                break;
            }

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
