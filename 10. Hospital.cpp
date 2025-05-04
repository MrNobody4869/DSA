#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Structure to represent a patient
struct Patient {
    string name;
    int priority; // 1 = Serious, 2 = Non-serious, 3 = General

    // Overload < to make min-heap using priority
    bool operator<(const Patient& other) const {
        return priority > other.priority; // lower priority value = higher actual priority
    }
};

int main() {
    priority_queue<Patient> hospitalQueue; // Min-heap based on priority

    int choice;
    do {
        cout << "\n--- Hospital Priority Queue ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Next Patient\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Patient p;
                cout << "Enter patient name: ";
                cin.ignore();
                getline(cin, p.name);

                cout << "Select condition:\n";
                cout << "1. Serious\n2. Non-serious\n3. General Checkup\n";
                cout << "Enter choice: ";
                cin >> p.priority;

                hospitalQueue.push(p); // Add patient to queue
                cout << "Patient added to queue.\n";
                break;
            }
            case 2:
                if (!hospitalQueue.empty()) {
                    Patient next = hospitalQueue.top(); // Get highest priority
                    hospitalQueue.pop(); // Remove from queue
                    cout << "Serving patient: " << next.name << " (Priority " << next.priority << ")\n";
                } else {
                    cout << "No patients in the queue.\n";
                }
                break;

            case 3:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);

    return 0;
}
