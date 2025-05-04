#include <iostream> // For standard input/output
using namespace std;

// Node structure for the BST
class Node {
public:
    int data;       // Stores the value of the node
    Node* left;     // Pointer to left child
    Node* right;    // Pointer to right child

    Node(int val) {         // Constructor to initialize node
        data = val;         // Assign the value
        left = NULL;        // Initially left child is null
        right = NULL;       // Initially right child is null
    }
};

// Function to insert a node into BST
Node* insert(Node* root, int val) {
    if (root == NULL)                 // If tree is empty, create a new node as root
        return new Node(val);
    if (val < root->data)             // If value is less, go to left subtree
        root->left = insert(root->left, val);
    else                              // If value is greater or equal, go to right subtree
        root->right = insert(root->right, val);
    return root;                      // Return the root (unchanged)
}

// Function to calculate the height / longest path from root
int longestPath(Node* root) {
    if (root == NULL) return 0;             // Base case: empty tree has 0 height
    int left = longestPath(root->left);     // Recursively find height of left subtree
    int right = longestPath(root->right);   // Recursively find height of right subtree
    return max(left, right) + 1;            // Height is max of left/right + current node
}

// Function to find the minimum value node in BST
int findMin(Node* root) {
    if (root == NULL) return -1;            // If tree is empty
    while (root->left != NULL)              // Keep going left
        root = root->left;
    return root->data;                      // Leftmost node is the minimum
}

// Function to swap left and right pointers (mirror the tree)
void swapNodes(Node* root) {
    if (root == NULL) return;               // Base case
    swap(root->left, root->right);          // Swap left and right pointers
    swapNodes(root->left);                  // Recursively swap left subtree
    swapNodes(root->right);                 // Recursively swap right subtree
}

// Function to search a value in BST
bool search(Node* root, int val) {
    if (root == NULL) return false;         // If tree is empty, return false
    if (val == root->data) return true;     // Value found
    if (val < root->data)                   // If value is less, search left
        return search(root->left, val);
    else                                    // Else, search right
        return search(root->right, val);
}

// Main function
int main() {
    Node* root = NULL;                      // Start with an empty tree
    int choice, val;                        // For menu input

    int n;                                  // Number of initial nodes
    cout << "Enter number of initial nodes to insert: ";
    cin >> n;                               // Read number of nodes
    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; ++i) {           // Insert initial values into BST
        cin >> val;
        root = insert(root, val);
    }

    // Menu loop for user operations
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert new node\n";
        cout << "2. Find longest path from root\n";
        cout << "3. Find minimum value in tree\n";
        cout << "4. Swap left and right pointers\n";
        cout << "5. Search a value\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;                      // Read user choice

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;                 // Get value from user
                root = insert(root, val);   // Insert value into tree
                cout << "Node inserted.\n";
                break;

            case 2:
                cout << "Longest path (tree height): " << longestPath(root) << "\n";
                break;

            case 3:
                cout << "Minimum value: " << findMin(root) << "\n";
                break;

            case 4:
                swapNodes(root);            // Mirror the tree
                cout << "Tree has been mirrored.\n";
                break;

            case 5:
                cout << "Enter value to search: ";
                cin >> val;                 // Get value to search
                if (search(root, val))      // Search and print result
                    cout << "Value found in the tree.\n";
                else
                    cout << "Value NOT found.\n";
                break;

            case 6:
                cout << "Exiting program.\n";
                return 0;                   // Exit the program

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}




/*
Concepts Used:

1. Binary Search Tree (BST):
   - A tree where each node has at most two children.
   - Left child < parent, Right child >= parent.

2. Insert:
   - Recursive approach to find correct location and insert the new node.

3. Longest Path:
   - Uses recursion to find the height (max depth) of left and right subtrees.

4. Find Minimum:
   - Leftmost node in a BST always holds the minimum value.

5. Swap Nodes:
   - Recursively swaps left and right children of all nodes — produces a mirror image.

6. Search:
   - Standard binary search logic applied to tree structure.
*/
