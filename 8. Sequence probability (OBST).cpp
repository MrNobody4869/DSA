#include <iostream>  // For input-output operations
#include <vector>    // To store keys and probabilities in dynamic arrays
#include <limits>    // For getting infinity (used to find minimum cost)
using namespace std;

// Structure to represent a node in the OBST
struct Node {
    int key;           // Key value
    float prob;        // Search probability
    Node* left;        // Pointer to left subtree
    Node* right;       // Pointer to right subtree

    // Constructor
    Node(int k, float p) {
        key = k;
        prob = p;
        left = right = nullptr;
    }
};

// Function to calculate the sum of probabilities from i to j
float sumProb(const vector<Node*>& keys, int i, int j) {
    float sum = 0;
    for (int k = i; k <= j; ++k)
        sum += keys[k]->prob;
    return sum;
}

// Function to calculate the optimal cost of OBST
float optimalCost(const vector<Node*>& keys, int i, int j) {
    if (i > j) return 0; // Base case: no keys

    float minCost = numeric_limits<float>::infinity();  // Start with a very large number

    // Try making each key in range i to j the root
    for (int r = i; r <= j; ++r) {
        float costLeft = optimalCost(keys, i, r - 1);   // Cost of left subtree
        float costRight = optimalCost(keys, r + 1, j);  // Cost of right subtree
        float totalCost = costLeft + costRight;

        if (totalCost < minCost)
            minCost = totalCost;
    }

    // Total cost includes the sum of probabilities for this range
    return minCost + sumProb(keys, i, j);
}

// Function to construct the OBST and return the root
Node* constructOBST(const vector<Node*>& keys, int i, int j) {
    if (i > j) return nullptr; // Base case

    float minCost = numeric_limits<float>::infinity();
    int rootIndex = i;

    // Find the index with minimum total cost
    for (int r = i; r <= j; ++r) {
        float cost = optimalCost(keys, i, r - 1) + optimalCost(keys, r + 1, j);
        if (cost < minCost) {
            minCost = cost;
            rootIndex = r;
        }
    }

    // Create the root node
    Node* root = new Node(keys[rootIndex]->key, keys[rootIndex]->prob);

    // Recursively construct left and right subtrees
    root->left = constructOBST(keys, i, rootIndex - 1);
    root->right = constructOBST(keys, rootIndex + 1, j);

    return root;
}

// Function to display the OBST (in-order traversal)
void printTree(Node* root, string indent = "", bool isLeft = true) {
    if (root != nullptr) {
        cout << indent;
        if (isLeft)
            cout << "L----";
        else
            cout << "R----";
        cout << "Key: " << root->key << " | Prob: " << root->prob << endl;
        printTree(root->left, indent + "     ", true);
        printTree(root->right, indent + "     ", false);
    }
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    vector<Node*> keys;  // Vector of node pointers

    // Input the keys and their probabilities
    for (int i = 0; i < n; ++i) {
        int key;
        float p;
        cout << "Enter key " << i + 1 << ": ";
        cin >> key;
        cout << "Enter probability for key " << key << ": ";
        cin >> p;
        keys.push_back(new Node(key, p));
    }

    // Construct the OBST
    Node* root = constructOBST(keys, 0, n - 1);

    // Print the OBST
    cout << "\nOptimal Binary Search Tree (OBST):\n";
    printTree(root);

    // Print the optimal cost
    float min_cost = optimalCost(keys, 0, n - 1);
    cout << "\nMinimum expected search cost: " << min_cost << endl;

    return 0;
}



/*
THEORY OF CONCEPTS USED:

1. Binary Search Tree (BST):
   - A tree structure where each node has up to 2 children.
   - Left child < Root < Right child.
   - Efficient for search, insertion, and deletion in O(log n) average time.

2. Optimal Binary Search Tree (OBST):
   - A BST that minimizes the **expected search cost** based on access probabilities of keys.
   - Goal: Build a BST where frequently accessed keys are placed nearer to the root.

3. Expected Search Cost:
   - The sum of each key's search probability × its depth in the tree.
   - OBST minimizes this cost.

4. Probability:
   - Each key has a probability (given by the user) indicating how frequently it is accessed.
   - Sum of all probabilities ≤ 1.

5. Recursive Cost Calculation (optimalCost function):
   - Calculates cost of all possible BSTs and selects the one with minimum cost.
   - For each possible root `r` in a range `i` to `j`:
     TotalCost = Cost(left subtree) + Cost(right subtree) + Sum of probabilities (i to j)
   - This is a pure recursive solution and has **exponential time complexity**: O(2^n)

6. Constructing the OBST (constructOBST function):
   - Recursively chooses root with minimum total cost (calculated using optimalCost).
   - Builds left and right subtrees using the same logic.

7. Node Structure:
   - Each node contains:
     - `key`: the value stored
     - `prob`: the probability of access
     - `left` and `right`: pointers to children

8. sumProb function:
   - Helper function to compute sum of probabilities in range [i, j].

9. printTree function:
   - In-order traversal that visually prints the tree structure.
   - Uses indentation and left/right labeling for readability.

10. Time and Space Complexity:
    - Current approach: Exponential time due to repeated subproblem calculations (no memoization).
    - Space: O(n) for tree and recursion stack.
    - Can be optimized to O(n^3) using Dynamic Programming (DP-based OBST).

REAL-WORLD APPLICATIONS:
- Efficient dictionary or database indexing where keys are not accessed uniformly.
- Compiler symbol table optimization.
- Data compression and encoding (like Huffman coding with additional constraints).

IMPROVEMENT TIP:
- Replace recursive `optimalCost` with a DP table to improve efficiency.
*/

