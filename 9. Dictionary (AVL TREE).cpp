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

// Update a keyword meaning (same as insert for updating)
Node* update(Node* node, string key, string meaning) {
    return insert(node, key, meaning);
}

// Delete a keyword from the AVL tree
Node* deleteNode(Node* root, string key) {
    if (!root) return root;

    // Perform standard BST delete
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else { // Found the node to be deleted
        // Node with one child or no child
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children
        Node* temp = root->right; // Get the inorder successor (smallest in the right subtree)
        while (temp && temp->left) temp = temp->left;

        root->key = temp->key;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->key); // Delete the inorder successor
    }

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Get balance factor
    int balance = getBalance(root);

    // Perform rotations
    if (balance > 1 && getBalance(root->left) >= 0)  // Left Left
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {  // Left Right
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {  // Right Right
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {  // Right Left
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
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
        cout << "2. Delete Keyword\n";
        cout << "3. Display Ascending\n";
        cout << "4. Display Descending\n";
        cout << "5. Search Keyword\n";
        cout << "6. Exit\n";
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
                cout << "Enter keyword to delete: ";
                cin >> key;
                root = deleteNode(root, key);
                break;

            case 3:
                cout << "\nDictionary (Ascending Order):\n";
                displayAscending(root);
                break;

            case 4:
                cout << "\nDictionary (Descending Order):\n";
                displayDescending(root);
                break;

            case 5: {
                cout << "Enter keyword to search: ";
                cin >> key;
                int comparisons = 0;
                search(root, key, comparisons);
                break;
            }

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}


/*
THEORY OF CONCEPTS USED:
Space and TIme complexity:
Best, Avg, Worst is O(Log n) for all, search, insert, delete, update.
for traversal (Asc/Desc) it is O(n) for all best, avg, worst

1. AVL Tree (Adelson-Velsky and Landis Tree):
   - A self-balancing Binary Search Tree (BST).
   - After every insertion and deletion, it checks and restores balance using rotations.
   - Balance factor = height(left subtree) - height(right subtree)
     - Must always be in range [-1, 0, +1].

2. Dictionary Using AVL:
   - Each node stores a keyword (string) and its meaning.
   - Efficient for operations like insertion, deletion, search, and update due to AVL balancing.

3. Node Structure:
   - Contains:
     - `key`: keyword (string)
     - `meaning`: string value
     - `left` and `right`: child pointers
     - `height`: used to compute balance factor for rotations

4. Rotations (for balancing):
   - **Right Rotation (LL Case):** Unbalanced due to insertion in left-left.
   - **Left Rotation (RR Case):** Unbalanced due to insertion in right-right.
   - **Left-Right Rotation (LR Case):** Left child is right-heavy.
   - **Right-Left Rotation (RL Case):** Right child is left-heavy.

5. Insert Operation:
   - Follows BST logic.
   - Updates height, checks balance factor.
   - Performs rotations if tree becomes unbalanced.

6. Delete Operation:
   - Handles three cases:
     - Node has no child.
     - Node has one child.
     - Node has two children (in-order successor is used).
   - After deletion, height and balance are updated, and rotations are applied if needed.

7. Update Operation:
   - Same as insert: if key already exists, its meaning is updated.

8. Traversals:
   - **In-order Traversal (Ascending):** Displays dictionary in alphabetical order.
   - **Reverse In-order (Descending):** Displays in reverse alphabetical order.

9. Search Operation:
   - BST-style recursive search.
   - Counts number of key comparisons for performance analysis.

10. Time Complexities:
    - **Search/Insert/Delete:** O(log n) due to self-balancing.
    - **Space Complexity:** O(n) for storing n nodes.

11. Comparison Counting:
    - Tracks number of comparisons during search.
    - Useful to measure performance or efficiency.

12. Menu-Driven Program:
    - Allows interactive operations:
      - Add/update, delete, display ascending/descending, search, exit.

APPLICATIONS:
- Used in implementing dictionaries, databases, and auto-complete systems.
- Suitable where dynamic insertion/deletion with fast look-up is required.

NOTE:
- AVL tree guarantees better worst-case performance than an unbalanced BST.
- Ensure to use `cin.ignore()` before `getline()` to avoid input skipping.

IMPROVEMENT TIPS:
- Memory cleanup (free/delete tree on exit) can be added.
- Case-insensitive comparison for user-friendliness (using `transform` to lowercase).
*/

