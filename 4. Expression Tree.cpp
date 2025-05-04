#include <iostream>     // Includes standard input and output operations
#include <stack>        // Includes the stack container from STL for stack-based operations
#include <cctype>       // Includes functions like isalpha to check character types
using namespace std;    // To avoid prefixing std:: before standard names like cout, cin, stack

// Structure to define a node in the expression tree
struct TreeNode {
    char data;               // Stores the character (operand or operator)
    TreeNode* left;          // Pointer to the left child of the node
    TreeNode* right;         // Pointer to the right child of the node

    // Constructor to initialize node with character value
    TreeNode(char val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');  // Returns true if character is any arithmetic operator
}

// Function to construct expression tree from given prefix expression
TreeNode* constructExpressionTree(const string& prefix) {
    stack<TreeNode*> st;                      // Create a stack to hold TreeNode pointers

    // Traverse the prefix expression from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];                  // Get current character from the expression

        if (isalpha(c)) {                    // Check if current character is an operand
            TreeNode* node = new TreeNode(c);  // Create a new node with operand
            st.push(node);                   // Push the node to stack since operand needs no processing yet
        } else if (isOperator(c)) {          // Check if the current character is an operator
            TreeNode* node = new TreeNode(c);  // Create a new node for the operator
            TreeNode* left = st.top(); st.pop();   // Pop the top node from stack as left child
            TreeNode* right = st.top(); st.pop();  // Pop the next node from stack as right child
            node->left = left;              // Set left child
            node->right = right;            // Set right child
            st.push(node);                  // Push the new subtree root back to stack
        }
    }
    return st.top();                         // Final element in stack is the root of the complete tree
}

// Function to perform post-order traversal without recursion
void postOrderTraversal(TreeNode* root) {
    if (!root) return;                       // If tree is empty, no traversal needed

    stack<TreeNode*> s1, s2;                 // Two stacks: one for processing nodes, one for storing post-order
    s1.push(root);                           // Start with root node pushed to first stack

    // Loop until all nodes are processed
    while (!s1.empty()) {
        TreeNode* curr = s1.top(); s1.pop(); // Get top node from s1
        s2.push(curr);                       // Push it into s2 to reverse the process order

        if (curr->left) s1.push(curr->left);   // Push left child (processed later)
        if (curr->right) s1.push(curr->right); // Push right child (processed before left)
    }

    // Now s2 contains nodes in reverse post-order, so print them
    while (!s2.empty()) {
        cout << s2.top()->data << " ";       // Print node data in correct post-order
        s2.pop();
    }
    cout << endl;
}

// Function to delete all nodes of the tree (post-order deletion)
void deleteTree(TreeNode* root) {
    if (!root) return;                       // If root is null, nothing to delete

    stack<TreeNode*> st;                     // Stack to hold nodes to be deleted
    st.push(root);                           // Start from root

    while (!st.empty()) {
        TreeNode* curr = st.top(); st.pop();   // Pop node from stack

        if (curr->left) st.push(curr->left);   // Push left child if it exists
        if (curr->right) st.push(curr->right); // Push right child if it exists

        delete curr;                           // Delete the current node
    }
}

// Main function with menu-driven interface
int main() {
    TreeNode* root = nullptr;           // Root pointer of the expression tree
    string prefix;                      // Variable to store prefix expression from user
    int choice;                         // Variable to store user menu selection

    do {
        // Display menu options to user
        cout << "\n--- Expression Tree Menu ---\n";
        cout << "1. Enter Prefix Expression\n";
        cout << "2. Construct Expression Tree\n";
        cout << "3. Postorder Traversal (Non-Recursive)\n";
        cout << "4. Delete Expression Tree\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;                  // Take user input

        switch (choice) {
            case 1:
                cout << "Enter prefix expression: ";
                cin >> prefix;         // Store entered prefix expression
                break;

            case 2:
                if (prefix.empty()) {
                    cout << "Enter prefix expression first (Option 1).\n";
                } else {
                    root = constructExpressionTree(prefix);  // Build expression tree
                    cout << "Expression tree constructed successfully.\n";
                }
                break;

            case 3:
                if (!root) {
                    cout << "No tree to traverse. Please construct it first.\n";
                } else {
                    cout << "Postorder Traversal: ";
                    postOrderTraversal(root);  // Perform post-order traversal
                }
                break;

            case 4:
                if (!root) {
                    cout << "Tree is already deleted or not constructed.\n";
                } else {
                    deleteTree(root);         // Delete all nodes in the tree
                    root = nullptr;           // Reset root to null
                    cout << "Expression tree deleted.\n";
                }
                break;

            case 5:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Please select again.\n";
        }
    } while (choice != 5);              // Repeat menu until user chooses to exit

    return 0;
}

/*
----------------------------
Conceptual Explanation:
----------------------------
1. Expression Tree:
   - A binary tree where leaves are operands (a, b, c, etc.) and internal nodes are operators (+, -, *, /).
   - Useful for evaluating expressions and converting between different forms (prefix, infix, postfix).

2. Prefix Expression:
   - Operators precede their operands. Example: +--a*bc/def

3. Tree Construction:
   - Constructed from prefix by scanning right to left.
   - Operands become leaf nodes directly.
   - Operators create new internal nodes by attaching two top stack nodes as children.

4. Postorder Traversal (Non-Recursive):
   - Traverse left subtree, then right subtree, then root.
   - Simulated with two stacks to avoid recursion.

5. Tree Deletion:
   - Done using post-order traversal again.
   - Ensures child nodes are deleted before parent nodes.

6. Stack:
   - LIFO structure is ideal for handling tree building and traversal tasks efficiently.
*/
