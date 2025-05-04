#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Structure to store student data
struct Student {
    int rollNo;
    string name;
    string division;
    string address;
};

// Function to add a student record to the file
void addStudent(const string& filename) {
    Student student;
    ofstream outFile(filename, ios::app); // Open file in append mode

    cout << "Enter Roll Number: ";
    cin >> student.rollNo;
    cin.ignore(); // To ignore the newline character after the roll number input

    cout << "Enter Name: ";
    getline(cin, student.name);

    cout << "Enter Division: ";
    getline(cin, student.division);

    cout << "Enter Address: ";
    getline(cin, student.address);

    outFile.write(reinterpret_cast<char*>(&student), sizeof(student));
    outFile.close();

    cout << "Student added successfully!" << endl;
}

// Function to display a student record
void displayStudent(const string& filename, int rollNo) {
    Student student;
    ifstream inFile(filename, ios::binary); // Open file in binary mode

    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.rollNo == rollNo) {
            cout << "\nStudent Details:\n";
            cout << "Roll Number: " << student.rollNo << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No student found with Roll Number: " << rollNo << endl;
    }

    inFile.close();
}

// Function to delete a student record from the file
void deleteStudent(const string& filename, int rollNo) {
    Student student;
    ifstream inFile(filename, ios::binary);
    ofstream tempFile("temp.dat", ios::binary); // Temporary file to store valid data

    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.rollNo == rollNo) {
            found = true; // Skip writing this record to the temp file
            continue;
        }
        tempFile.write(reinterpret_cast<char*>(&student), sizeof(student));
    }

    if (found) {
        cout << "Student with Roll Number " << rollNo << " deleted successfully!" << endl;
        inFile.close();
        tempFile.close();
        remove(filename.c_str()); // Delete the original file
        rename("temp.dat", filename.c_str()); // Rename the temp file as the original file
    } else {
        cout << "No student found with Roll Number: " << rollNo << endl;
        inFile.close();
        tempFile.close();
        remove("temp.dat"); // Remove the temporary file
    }
}

// Main menu function
void displayMenu() {
    cout << "\n1. Add Student\n";
    cout << "2. Display Student\n";
    cout << "3. Delete Student\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    string filename = "students.dat"; // File to store student data
    int choice, rollNo;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(filename);
                break;

            case 2:
                cout << "Enter Roll Number to search: ";
                cin >> rollNo;
                displayStudent(filename, rollNo);
                break;

            case 3:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNo;
                deleteStudent(filename, rollNo);
                break;

            case 4:
                cout << "Exiting program..." << endl;
                return 0;

            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }

    return 0;
}
