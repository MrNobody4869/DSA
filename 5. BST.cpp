#include <iostream>                     // For standard input and output
#include <string>                       // For using string data type
using namespace std;

// Structure to represent a dictionary node
struct Node {
    string key;                         // The keyword (key)
    string meaning;                     // The meaning associated with the key
    Node* left;                         // Pointer to left child
    Node* right;                        // Pointer to right child
};

// Function to create a new node with given key and meaning
Node* createNode(string key, string meaning) {
    Node* temp = new Node();           // Allocate memory for new node
    temp->key = key;                   // Set key
    temp->meaning = meaning;           // Set meaning
    temp->left = temp->right = nullptr;// Initialize children to nullptr
    return temp;                       // Return new node
}

// Function to insert a node into the BST
Node* insert(Node* root, Node* temp) {
    if (root == nullptr) {
        return temp;                   // If tree is empty, new node becomes root
    }
    if (temp->key < root->key) {       // If key is smaller, go left
        root->left = insert(root->left, temp);
    } else if (temp->key > root->key) {// If key is greater, go right
        root->right = insert(root->right, temp);
    } else {
        cout << "Duplicate key. Not inserting.\n"; // Reject duplicates
    }
    return root;                       // Return unchanged root
}

// Function to perform in-order traversal (Ascending order)
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);           // Visit left subtree
        cout << root->key << ": " << root->meaning << endl; // Print node
        inorder(root->right);          // Visit right subtree
    }
}

// Function to perform reverse in-order traversal (Descending order)
void reverseInorder(Node* root) {
    if (root != nullptr) {
        reverseInorder(root->right);   // Visit right subtree first
        cout << root->key << ": " << root->meaning << endl;
        reverseInorder(root->left);    // Visit left subtree
    }
}

// Function to search a keyword and count comparisons
int search(Node* root, string key, int& comparisons) {
    while (root != nullptr) {
        comparisons++;                 // Increment comparison count
        if (key == root->key) {
            cout << "Found: " << root->meaning << endl;
            return comparisons;
        } else if (key < root->key) {
            root = root->left;         // Search in left subtree
        } else {
            root = root->right;        // Search in right subtree
        }
    }
    cout << "Keyword not found.\n";
    return comparisons;
}

// Function to find minimum node (used in deletion)
Node* findMin(Node* root) {
    while (root->left != nullptr) root = root->left;
    return root;
}

// Function to delete a node from the BST
Node* deleteNode(Node* root, string key) {
    if (root == nullptr) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key); // Go left
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key); // Go right
    } else {
        // Node found
        if (root->left == nullptr) {   // One or no child
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right); // Get inorder successor
        root->key = temp->key;             // Copy successor data
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->key); // Delete successor
    }
    return root;
}

// Function to update the meaning of an existing keyword
void update(Node* root, string key) {
    while (root != nullptr) {
        if (key == root->key) {
            cout << "Enter new meaning: ";
            getline(cin, root->meaning); // Update meaning
            cout << "Updated successfully.\n";
            return;
        } else if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    cout << "Keyword not found.\n";
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n2. Delete Keyword\n3. Update Meaning\n4. Display Ascending\n5. Display Descending\n6. Search Keyword\n7. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore(); // To clear newline after integer input

        switch (choice) {
            case 1:
                cout << "Enter keyword (Key): ";
                getline(cin, key);
                cout << "Enter meaning (Value): ";
                getline(cin, meaning);
                root = insert(root, createNode(key, meaning));
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                update(root, key);
                break;
            case 4:
                cout << "Dictionary in Ascending Order:\n";
                inorder(root);
                break;
            case 5:
                cout << "Dictionary in Descending Order:\n";
                reverseInorder(root);
                break;
            case 6:
                cout << "Enter keyword to search: ";
                getline(cin, key);
                {
                    int comps = 0;
                    int total = search(root, key, comps);
                    cout << "Comparisons made: " << total << endl;
                }
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}

/*
Concepts Used:

TIME COMPLEXITY (for average case):
-----------------------------------------------------------------------------------------
- Insertion     : O(log n)
- Deletion      : O(log n)
- Search        : O(log n)
- Update        : O(log n)
- Inorder/Rev   : O(n)
- Total space: O(log n) for avg and (n) for worst.

Note: Worst case becomes O(n) when BST is unbalanced (linear chain of nodes)

- Binary Search Tree: Efficient structure for insert/search/delete with O(log n) average time.
- Recursion: For insertion, traversal, and deletion.
- Stack memory usage minimized with iterative search/update/delete.
- Traversals help in sorting data (inorder for ascending, reverse inorder for descending).
- Comparison counting in search simulates worst-case time complexity analysis.

/*
- This program implements a dictionary using Binary Search Tree (BST).
- Each node contains:
  -> key (string) = keyword
  -> value (string) = meaning
  -> left and right child pointers

- Operations supported:
  1. Insert a new keyword and meaning
  2. Delete a keyword
  3. Update meaning of a keyword
  4. Display in ascending (inorder) and descending (reverse inorder) order
  5. Search a keyword and count comparisons

- Insert:
  -> If tree is empty, new node becomes root
  -> Otherwise, insert based on key comparison (left if smaller, right if larger)
  -> Duplicate keys are not allowed

- Delete:
  -> Search the node to delete
  -> Three cases:
     a) No child – delete node
     b) One child – link child to parent
     c) Two children – find inorder successor, copy data, delete successor

- Update:
  -> Search for key
  -> If found, update meaning

- Search:
  -> Traverse the tree using key comparison
  -> Count comparisons while searching

- Inorder Traversal:
  -> Prints dictionary in ascending order
  
- Reverse Inorder:
  -> Prints dictionary in descending order

- Space complexity for whole tree: O(n) for storing n nodes
- Extra space used in recursion: O(h) where h is tree height
*/

*/
