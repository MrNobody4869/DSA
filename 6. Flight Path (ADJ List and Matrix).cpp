#include <iostream> //cin and cout
#include <vector>// vector: for dynamic arrays like cities, visited, and adjacency lists
#include <string> // string: to handle city names and other text data
#include <unordered_map>// unordered_map: for representing the adjacency list (maps city index to a list of flights)


using namespace std;

// Edge structure to represent a flight
struct Edge {
    int destination;  // Destination city index
    int cost;         // Cost of the flight (time or fuel)
};

// Graph class to represent the flight network
class Graph {
private:
    vector<string> cities;                         // List of city names
    unordered_map<int, vector<Edge>> adjList;      // Adjacency list to represent flights

    // DFS helper function for checking connectivity
    void dfs(int city, vector<bool>& visited) {
        visited[city] = true;
        for (const Edge& e : adjList[city]) {
            if (!visited[e.destination]) {
                dfs(e.destination, visited);
            }
        }
    }

public:
    // Method to add a flight (edge) between two cities
    void addFlight(int source, int destination, int cost) {
        adjList[source].push_back(Edge{destination, cost});
        adjList[destination].push_back(Edge{source, cost}); // Assuming undirected graph
    }

    // Method to check if the graph is connected
    bool isConnected() {
        int numCities = cities.size();
        vector<bool> visited(numCities, false);
        dfs(0, visited); // Start DFS from the first city

        // Check if all cities have been visited
        for (bool v : visited) {
            if (!v) {
                return false;  // If any city is not visited, the network is not connected
            }
        }
        return true;  // All cities are visited, so the network is connected
    }

    // Method to display all the cities in the flight network
    void displayCities() {
        cout << "Cities in the flight network: \n";
        for (int i = 0; i < cities.size(); ++i) {
            cout << i + 1 << ". " << cities[i] << endl;
        }
    }

    // Method to set cities
    void setCities(const vector<string>& cityNames) {
        cities = cityNames;
    }

    // Method to display the flights
    void displayFlights() {
        cout << "\nFlight Network (Adjacency List Representation): \n";
        for (int i = 0; i < cities.size(); ++i) {
            cout << cities[i] << " -> ";
            for (const Edge& e : adjList[i]) {
                cout << cities[e.destination] << "(Cost: " << e.cost << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph flightNetwork;
    vector<string> cities;
    vector<tuple<int, int, int>> flights;
    int choice;

    // Menu-driven system
    do {
        // Displaying the menu
        cout << "\n=== Flight Network Menu ===\n";
        cout << "1. Set Cities\n";
        cout << "2. Add Flight\n";
        cout << "3. Display Cities\n";
        cout << "4. Display Flight Network\n";
        cout << "5. Check Connectivity\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Set Cities
                int numCities;
                cout << "\nEnter the number of cities: ";
                cin >> numCities;
                cities.clear();
                cin.ignore();
                cout << "Enter the names of the cities:\n";
                for (int i = 0; i < numCities; ++i) {
                    string city;
                    getline(cin, city);
                    cities.push_back(city);
                }
                flightNetwork.setCities(cities);
                break;
            }

            case 2: {
                // Add Flight
                int sourceIndex, destIndex, cost;
                flightNetwork.displayCities();  // Display the cities for the user to choose from
                cout << "Enter source city index (1-based): ";
                cin >> sourceIndex;
                cout << "Enter destination city index (1-based): ";
                cin >> destIndex;
                cout << "Enter the cost (time/fuel): ";
                cin >> cost;

                // Add flight to the network
                flightNetwork.addFlight(sourceIndex - 1, destIndex - 1, cost);
                cout << "Flight added successfully!\n";
                break;
            }

            case 3: {
                // Display Cities
                flightNetwork.displayCities();
                break;
            }

            case 4: {
                // Display Flight Network (Adjacency List)
                flightNetwork.displayFlights();
                break;
            }

            case 5: {
                // Check Connectivity
                if (flightNetwork.isConnected()) {
                    cout << "\nThe flight network is connected!" << endl;
                } else {
                    cout << "\nThe flight network is not connected." << endl;
                }
                break;
            }

            case 6: {
                // Exit
                cout << "Exiting the program...\n";
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);  // Loop until the user exits

    return 0;
}


/*
OVERALL TIME & SPACE COMPLEXITY:
- Adding a city: O(1)
- Adding a flight: O(1)

-> Graph Class: Represents the flight network using a cities vector (a list of city names) and an adjList unordered map (the adjacency list). 
   The map connects city indices to the flight connections (edges).
  - A data structure consisting of nodes (vertices) and connections (edges).
  - Used to model relationships like cities and flights in this problem.



3. Adjacency List:
   - A way to represent a graph where each node stores a list of connected nodes.
   - Space-efficient for sparse graphs (few connections compared to total possible).
   - Space Complexity: O(V + E), where V = number of cities, E = number of flights.

4. Depth-First Search (DFS):
   - A graph traversal algorithm that explores as far as possible along a branch before backtracking.
   - Used here to check if the graph is connected.
   - Time Complexity: O(V + E)
   - Space Complexity: O(V) for visited array and call stack

5. Connectivity in Graph:
   - A graph is connected if there is a path between every pair of nodes.
   - DFS from any node should visit all nodes in a connected graph.

6. Edge (Flight):
   - Represents a connection between two cities with a cost (fuel/time).
   - Stored as a struct with destination index and cost.

7. Vector:
   - A dynamic array from the C++ STL (Standard Template Library).
   - Used to store city names and adjacency lists.

8. unordered_map:
   - A hash table-based key-value data structure.
   - Used to map city indices to their adjacency lists for fast access.
   - Average Time Complexity: O(1) for insert and lookup

9. Tuple (in main function):
   - Temporarily used for holding flight data (source, destination, cost).
   - Not essential but useful if extending functionality.

10. Menu-Driven Program:
    - A simple console interface that allows user interaction.
    - Offers options like adding flights, checking connectivity, etc.

Justification for Adjacency List:

The adjacency list is space-efficient, especially when the number of flight paths is much smaller than the number of cities. 
This means it uses less memory compared to the adjacency matrix, which would use O(n^2) space even if most cities are not directly connected.
*/
