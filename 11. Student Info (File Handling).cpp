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



/*
THEORY OF CONCEPTS USED:

1. File Handling:
   - The ability to store, retrieve, and modify data in external files.
   - **ofstream** (output file stream) is used for writing data to files.
   - **ifstream** (input file stream) is used for reading data from files.
   - **ios::binary** mode is used to write/read the data in binary form for efficient storage and retrieval of structured data like `structs`.
   - **ios::app** mode allows new data to be appended to the file, without overwriting existing data.

2. Struct:
   - A **struct** (structure) is a user-defined data type used to group multiple variables of different types together.
   - In this program, the `Student` struct is used to represent a student with attributes:
     - `rollNo`: An integer representing the student's roll number.
     - `name`: A string holding the student's name.
     - `division`: A string representing the student's division.
     - `address`: A string holding the student's address.
   - Structs provide a simple way to represent and store related data.

3. Binary File Operations:
   - Binary files store data in raw form, which allows faster read and write operations compared to text files.
   - In this program, student data is written and read in **binary format** using `write()` and `read()`, which treats the data as raw memory.

4. Temporary File Usage:
   - When deleting a student, a **temporary file** (`temp.dat`) is used to store valid student records (excluding the one to be deleted).
   - After processing, the original file is deleted, and the temporary file is renamed to the original file name.
   - This approach ensures that the file data is safely modified without direct overwriting, which could cause data corruption.

5. File Pointer Management:
   - When opening files in binary mode, file pointers are automatically managed by the file streams (`ifstream` and `ofstream`).
   - **Reading** is done by advancing the file pointer to the next record in the file using `read()`, while **writing** advances it to the end in append mode.

6. Input Validation and User Interaction:
   - A simple **menu-driven interface** allows users to interact with the program:
     - Users can choose to add, display, delete, or exit the program.
     - The program uses **cin** and **getline** to take input from the user for student details.
   - **cin.ignore()** is used after reading integer input (`rollNo`) to handle the leftover newline character and prevent input skipping during string input.

7. Data Manipulation (Adding, Displaying, and Deleting Records):
   - **Add Student**: Collects student details, and writes them to the binary file.
   - **Display Student**: Reads the binary file record by record and shows the details of the student with the specified roll number.
   - **Delete Student**: Reads the file, skips the record to be deleted, and writes the remaining records to a temporary file, which is then renamed to replace the original file.

8. File Renaming and Deletion:
   - **rename()** is used to rename the temporary file to the original file name after deletion of the student record.
   - **remove()** is used to delete the original file before renaming the temporary file.

9. Program Control Flow:
   - The main loop continually displays the menu, allowing users to choose an operation.
   - The program uses a **switch-case** construct to control program flow based on user input (adding, displaying, deleting, or exiting).

10. Time Complexities:
    - **Add/Update**: O(1) for appending a student, as it simply writes the record to the end of the file.
    - **Display/Search**: O(n) for searching a student by roll number, as the program reads the file sequentially.
    - **Delete**: O(n) for deleting a student, as the program reads through the entire file to skip the record to be deleted.

11. Space Complexity:
    - **Space Complexity** is O(n) as the program stores student records in the file, with each record requiring memory for the struct's fields.

APPLICATIONS:
- This program can be used in small-scale student management systems, where student records need to be stored, retrieved, and modified efficiently.
- It is also applicable in educational institutions for managing student data like roll numbers, names, and addresses.

NOTE:
- **File handling** is crucial in data storage systems. Using binary files is more efficient than text files for structured data.
- **Temporary file handling** helps in safely modifying records without risking data corruption.

IMPROVEMENT TIPS:
- **Error Handling**: Add checks to ensure the file is open before reading/writing.
- **Memory Management**: For larger applications, consider using dynamic memory management (using pointers) and free/delete memory on exit.
- **Search Optimization**: Use a data structure (like hash maps) for more efficient searches (currently O(n)).
*/
