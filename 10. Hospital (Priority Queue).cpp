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




// Priority Queue:
// A priority queue is a type of queue where each element has a "priority" associated with it.
// Elements with higher priority are dequeued before those with lower priority.
// In C++, the priority_queue is implemented as a heap (binary tree) structure.
// By default, C++ uses a **max-heap**, where the largest element is at the top of the queue.
// To create a **min-heap** (where the smallest element has the highest priority),
// we need to customize the comparison operator to ensure that the element with the smallest priority value is dequeued first.


// Operator Overloading:
// In C++, you can define custom behavior for operators by overloading them.
// For instance, the `<` operator can be overloaded for a custom data structure.
// In this program, we overload the `<` operator for the `Patient` structure
// to compare based on the `priority` value. This ensures that the patient with the
// **lowest priority number** (i.e., highest priority like 'Serious') will be dequeued first.
// By overloading `<`, we modify the default behavior of the priority queue to treat it as a **min-heap**.


// Min-Heap:
// A **min-heap** is a binary tree where the key of each node is smaller than or equal to the keys of its children.
// This structure is used by the **priority_queue** to allow efficient retrieval of the element with the highest priority.
// In the context of the hospital system, this means that the patient with the most urgent condition (lowest priority number) is served first.
// The heap ensures that both insertion (adding a patient) and removal (serving a patient) happen in **logarithmic time**.


// Heap Operations:
// 1. **push()**: Adds a new patient to the priority queue. After adding the patient, the heap property is maintained
//    through a process called **heapification**, where the queue is restructured to keep the highest priority patient at the top.
//    The complexity of this operation is **O(log n)**, where `n` is the number of patients in the queue.
// 2. **top()**: Returns the element with the highest priority (root of the heap), but does not remove it from the queue.
//    The time complexity of this operation is **O(1)**, as the root of the heap can be accessed directly.
// 3. **pop()**: Removes the patient with the highest priority from the queue, and then **heapify** is called to restore the heap property.
//    This operation also has a time complexity of **O(log n)**.


// Menu-based System:
// The program is built around a **menu-driven system** that interacts with the user to allow:
// 1. **Adding a Patient**: The user can input a patient's name and condition (priority), and the patient is inserted into the priority queue.
// 2. **Serving the Next Patient**: The patient with the highest priority (lowest priority value) is removed from the queue and served.
// 3. **Exiting**: The program ends when the user chooses to exit.

// The queue operates on **first-come, first-served** for patients with the same priority value, but prioritizes patients
// based on the urgency of their medical conditions. This ensures that **serious patients** are always served before
// those requiring general checkups or non-serious treatments.
