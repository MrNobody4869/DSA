//problem statement: You have a business with several offices; you want to lease phone lines to connect them up with each other; 

#include <iostream>      // For input/output operations
#include <vector>        // For using vectors for storing edges and adjacency list
#include <cstdint>       // For using fixed width integers like INT32_MAX
#define MAX_NUM_CITIES 10  // Maximum cities (vertices) that can be input

using namespace std;

// Edge structure representing a path (edge) between two cities (vertices)
struct edge {
    int start;  // Starting city (vertex)
    int end;    // Destination city (vertex)
    int wt;     // Cost or weight of the connection (edge)
};

class graph {
    int adj_mat[MAX_NUM_CITIES][MAX_NUM_CITIES] = {0}; // Adjacency matrix for graph, holds cost between cities
    string city_names[MAX_NUM_CITIES];                 // Array of city names
    int city_count;                                    // Total number of cities
    edge mst[MAX_NUM_CITIES - 1];                      // Stores the edges in the MST
    void add_to_list(vector<edge> &, edge);            // Helper function to insert edge into sorted vector
    int cost;                                          // Total cost of MST

   public:
    graph();                 // Constructor to initialize the graph
    void prims_algo(int);    // Function to build MST using Prim's algorithm
    void display_mst();      // Display the MST and its total cost
};

// Helper function to add edge into the vector `list` sorted by weight (min first)
void graph::add_to_list(vector<edge> &list, edge e) {
    list.push_back(e);
    // Bubble it to correct position to keep list sorted
    for (int i = list.size() - 1; i > 0; i--) {
        if (list[i].wt < list[i - 1].wt) {
            swap(list[i], list[i - 1]);
        } else {
            break;
        }
    }
}

// Constructor: Initializes graph with cities and connections
graph::graph() {
    cost = 0;  // Start with 0 cost
    cout << "Number of cities are (1-" << MAX_NUM_CITIES << "):\t";
    cin >> city_count;
    // Clamp to max limit if exceeded
    city_count = (city_count > MAX_NUM_CITIES) ? MAX_NUM_CITIES : city_count;

    // Input city names
    for (int i = 0; i < city_count; i++) {
        cout << "Enter city:\n" << i + 1 << ":\t";
        cin >> city_names[i];
    }

    // Initialize adjacency matrix with high value (no path)
    for (int i = 0; i < city_count; i++)
        for (int j = 0; j < city_count; j++) 
            adj_mat[i][j] = INT32_MAX;

    int num_pairs;
    cout << "Number of city pairs are:\t";
    cin >> num_pairs;

    // Show city index (used as vertex ID) and name
    cout << "City codes are:\t" << endl;
    for (int i = 0; i < city_count; i++) {
        cout << i << " - " << city_names[i] << endl;
    }

    // Input the connections (edges) between city pairs
    int x, y, wt;
    for (int i = 0; i < num_pairs; i++) {
        cout << "Enter pair:\n" << i + 1 << ":\t";
        cin >> x >> y;
        cout << "Enter cost between city " << city_names[x] << " & city " << city_names[y] << ":\t";
        cin >> wt;
        adj_mat[x][y] = wt;  // Set cost in both directions since it's undirected
        adj_mat[y][x] = wt;
    }
}

// Function to implement Prim's algorithm
void graph::prims_algo(int start) {
    bool visited[MAX_NUM_CITIES] = {0};  // Track visited cities
    int visited_count = 1;               // Number of cities included in MST
    visited[start] = 1;                  // Mark start city as visited

    vector<edge> adj;                    // Candidate edges to explore

    // Add all edges from the starting city to the list
    for (int i = 0; i < city_count; i++) {
        if (adj_mat[start][i] != INT32_MAX) {
            edge e;
            e.start = start;
            e.end = i;
            e.wt = adj_mat[start][i];
            add_to_list(adj, e);         // Add edge to list sorted by weight
        }
    }

    // Loop until all cities are included in the MST
    while (visited_count != city_count) {
        edge m = adj.front();       // Pick minimum weight edge
        adj.erase(adj.begin());     // Remove it from list

        if (!visited[m.end]) {      // If destination city is not visited
            mst[visited_count - 1] = m;  // Add edge to MST
            cost += m.wt;                // Add cost to total MST cost

            // Explore all edges from newly added city
            for (int i = 0; i < city_count; i++) {
                if (adj_mat[m.end][i] != INT32_MAX) {
                    edge e;
                    e.start = m.end;
                    e.end = i;
                    e.wt = adj_mat[e.start][i];
                    add_to_list(adj, e);   // Add to candidate edges
                }
            }

            visited[m.end] = 1;   // Mark as visited
            visited_count++;      // Increment number of cities added
        }
    }
}

// Function to display the resulting Minimum Spanning Tree
void graph::display_mst() {
    cout << "Most efficient network is:\t" << endl;

    for (int i = 0; i < city_count - 1; i++) {
        // Show edge between city names with cost
        cout << city_names[mst[i].start] << " to " << city_names[mst[i].end]
             << " of weight " << mst[i].wt << endl;
    }

    // Total cost of building the network
    cout << endl << "The cost of network is:\t" << cost << endl;
}

int main() {
    // Initialize graph and input
    graph g;

    int start;
    cout << "Enter beginning city (city code 0-" << MAX_NUM_CITIES - 1 << "):\t";
    cin >> start;
    start = (start > MAX_NUM_CITIES - 1) ? 0 : start;  // Ensure valid input

    // Build MST and display result
    g.prims_algo(start);
    g.display_mst();

    return 0;
}
