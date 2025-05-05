#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Employee structure holding employee details
typedef struct employee {
    int empId;           // Employee ID (Unique identifier for the employee)
    char name[50];       // Name of the employee (String with a max length of 50 characters)
    char designation[50];// Job title or designation (String with a max length of 50 characters)
    int salary;          // Salary of the employee (integer value)
} employee;

// Index pair structure to map employee ID to file position
typedef struct index_pair {
    int key;            // Employee ID (acts as the key for indexing)
    int position;       // Position of the employee in the data file
} index_pair;

class employeeDatabase {
    string data_file_name = "ind_employee_data.dat";    // Data file for employee information
    string index_file_name = "ind_employee_index.dat";  // Index file to map employee ID to position in data file
public:
    employeeDatabase();  // Constructor to initialize files if they don't exist
    void addEmployee(int eid, char name[50], char dest[50], int sal);  // Adds employee to both data and index files
    void searchEmployee(int);  // Searches for employee by ID
    void deleteEmployee(int);  // Deletes employee record from both files
    bool isPresent(int);  // Checks if an employee already exists in the system
    void display_all();  // Displays all employee records
    employee readEmp(int pos);  // Reads an employee from a given position in the data file
};

// Function to read an employee from a given position in the data file
employee employeeDatabase::readEmp(int pos) {
    fstream data_file(data_file_name, ios::binary | ios::in | ios::ate);
    employee emp;
    
    // Check if the position is valid (it should not exceed the file size)
    if (pos >= data_file.tellg() || pos == -1) {
        emp.empId = -1;  // Set empId to -1 to indicate invalid record
        return emp;
    }
    
    // Move the file pointer to the specified position
    data_file.seekg(pos, ios::beg);
    data_file.read((char *)&emp, sizeof(emp));  // Read the employee data from the file
    data_file.close();
    return emp;
}

// Constructor: Initializes the data and index files if they don't exist
employeeDatabase::employeeDatabase() {
    fstream data_file(data_file_name);
    fstream index_file(index_file_name);
    
    // Check if the data and index files already exist
    if (data_file.fail() | index_file.fail()) {
        cout << "Created a new file." << endl;
        // Create new files if they don't exist
        data_file.open(data_file_name, ios::binary | ios::out | ios::app);
        index_file.open(index_file_name, ios::binary | ios::out | ios::app);
    } else {
        cout << "File already exists." << endl;
    }
    data_file.close();
    index_file.close();
}

// Function to add an employee to the data file and update the index file
void employeeDatabase::addEmployee(int eid, char name[50], char dest[50], int sal) {
    fstream data_file(data_file_name, ios::binary | ios::out | ios::app);
    fstream index_file(index_file_name, ios::binary | ios::in);
    index_pair current, temp;
    char *all_data;
    employee emp;
    int pos, ipos;
    bool update = false;

    // Check if employee already exists in the index file
    while (index_file.read((char *)&current, sizeof(index_pair))) {
        if (current.key == eid) {  // If employee ID matches
            if (current.position == -1) {  // If position is -1, the record needs updating
                ipos = (int)index_file.tellg() - sizeof(current);
                update = true;
                break;
            } else {
                cout << "Cannot add employee, already exists." << endl;
                goto exit_addEmployee;  // Exit if employee already exists
            }
        }
    }
    index_file.close();

    // Prepare new employee data to be written
    emp.empId = eid;
    strcpy(emp.name, name);  // Copy name into employee structure
    strcpy(emp.designation, dest);  // Copy designation into employee structure
    emp.salary = sal;  // Assign salary to employee structure

    data_file.seekp(0, ios::end);  // Move the file pointer to the end of the data file
    pos = data_file.tellp();  // Get the position where the new record will be written
    data_file.write((char *)&emp, sizeof(emp));  // Write the employee data to the data file
    current.key = eid;  // Set the key (employee ID)
    current.position = pos;  // Set the position (where the record was written)

    // If the employee is being updated, write to the correct position in the index file
    if (update) {
        index_file.open(index_file_name, ios::binary | ios::out);
        index_file.seekp(ipos, ios::beg);  // Move file pointer to the correct position
        index_file.write((char *)&current, sizeof(current));  // Update the index file
    } else {
        bool written = false;
        vector<index_pair> index_pairs;
        
        // Open the index file to read and insert the new record in sorted order
        index_file.open(index_file_name, ios::binary | ios::in);
        while (index_file.read((char *)&temp, sizeof(index_pair))) {
            if (!written && temp.key > eid) {  // Insert the new record at the correct position
                written = true;
                index_pairs.push_back(current);
            }
            index_pairs.push_back(temp);
        }
        if (!written) {
            index_pairs.push_back(current);  // Append if the new record is the last one
        }

        index_file.clear();
        index_file.close();

        // Write the updated index to the index file
        index_file.open(index_file_name, ios::binary | ios::out);
        for (int i = 0; i < index_pairs.size(); i++) {
            current = index_pairs[i];
            if (current.position != -1) {
                index_file.write((char *)&current, sizeof(index_pair));  // Write valid index entries
            }
        }
    }
    cout << "Employee added successfully." << endl;

exit_addEmployee:
    data_file.close();
    index_file.close();
}

// Function to display employee information
void display_emp(employee emp) {
    cout << "ID:\t" << emp.empId << endl;
    cout << "Name:\t" << emp.name << endl;
    cout << "Designation:\t" << emp.designation << endl;
    cout << "Salary:\tRs. " << emp.salary << endl;
}

// Function to search for an employee by employee ID
void employeeDatabase::searchEmployee(int eid) {
    fstream index_file(index_file_name, ios::binary | ios::in);
    index_pair current;
    int pos = -1;

    // Search the index file for the employee ID
    while (index_file.read((char *)&current, sizeof(index_pair))) {
        if (current.key == eid) {
            pos = current.position;  // Get the position of the employee record
            break;
        }
    }

    employee emp = readEmp(pos);  // Retrieve the employee data from the data file
    if (emp.empId == -1) {
        cout << "Employee does not exist." << endl;  // If no record is found
    } else {
        cout << "--- EMPLOYEE FOUND ---" << endl;
        display_emp(emp);  // Display the employee details
        cout << "--- END OF RECORD ---" << endl;
    }

    index_file.close();
}

// Function to check if an employee exists in the index file
bool employeeDatabase::isPresent(int eid) {
    fstream index_file(index_file_name, ios::binary | ios::in);
    index_pair current;

    // Search through the index file
    while (index_file.read((char *)&current, sizeof(index_pair))) {
        if (current.key == eid) {
            if (current.position == -1) {  // If the position is invalid, return false
                index_file.close();
                return false;
            } else {
                index_file.close();
                return true;  // If employee exists, return true
            }
        }
    }
    index_file.close();
    return false;
}

// Function to delete an employee record from the data and index files
void employeeDatabase::deleteEmployee(int eid) {
    fstream index_file(index_file_name, ios::binary | ios::in);
    index_pair current; 
    bool deleted = false;
    vector<index_pair> pairs;

    // Read the index file and remove the employee from the index list
    while (index_file.read((char *)&current, sizeof(index_pair))) {
        if (current.key == eid) {
            deleted = true;  // Mark the employee as deleted
        } else {
            pairs.push_back(current);  // Keep valid entries
        }
    }
    index_file.close();
    if (deleted) {
        // Re-open index file and write the updated index
        index_file.open(index_file_name, ios::binary | ios::out);
        index_file.clear();
        index_file.seekp(0, ios::beg);

        for (int i = 0; i < pairs.size(); i++) {
            current = pairs[i];
            index_file.write((char *)&current, sizeof(index_pair));  // Write remaining pairs
        }
        index_file.close();

        cout << "Employee deleted successfully." << endl;
    } else {
        cout << "Employee does not exist." << endl;
    }
}

// Function to display all employees
void employeeDatabase::display_all() {
    fstream index_file(index_file_name, ios::binary | ios::in);
    index_pair current;
    int pos;

    // Read through the index file and display all valid employees
    while (index_file.read((char *)&current, sizeof(index_pair))) {
        if (current.position != -1) {
            pos = current.position;
            employee emp = readEmp(pos);  // Get employee record by position
            display_emp(emp);  // Display the employee details
        }
    }
    index_file.close();
}

// Main function to interact with the employee management system
int main() {
    employeeDatabase db;
    int choice, id, salary;
    char name[50], designation[50];

    do {
        cout << "---- Employee Database ----\n";
        cout << "1. Add Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Display All Employees\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Add employee
                cout << "Enter Employee ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();  // Ignore leftover newline
                cin.getline(name, 50);
                cout << "Enter Designation: ";
                cin.getline(designation, 50);
                cout << "Enter Salary: ";
                cin >> salary;
                db.addEmployee(id, name, designation, salary);
                break;
            case 2: // Search employee
                cout << "Enter Employee ID to search: ";
                cin >> id;
                db.searchEmployee(id);
                break;
            case 3: // Delete employee
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                db.deleteEmployee(id);
                break;
            case 4: // Display all employees
                db.display_all();
                break;
            case 5: // Exit
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);  // Keep running until the user chooses to exit

    return 0;
}




/*
THEORY OF CONCEPTS USED:

1. File Handling:
   - The program uses **sequential binary files** for storing employee data and an index file for efficiently mapping employee IDs to their positions in the data file.
   - **fstream** is used for both reading and writing operations on the binary files.
   - **ios::binary** mode is used to store the data in raw form for more efficient read/write operations.
   - **ios::app** mode appends data to the file without overwriting existing records.

2. Employee Structure:
   - The **employee struct** stores the details of an employee:
     - `empId`: Employee ID (integer)
     - `name`: Employee name (character array)
     - `designation`: Job title (character array)
     - `salary`: Employee salary (integer)
   - This structure allows the program to group multiple related fields together in a compact format for efficient storage.

3. Index Pair Structure:
   - The **index_pair struct** maps the employee ID (`key`) to the corresponding position in the data file (`position`).
   - This helps in quickly locating the employee record by searching the index file instead of scanning the entire data file.

4. Binary File Operations:
   - Employee records are written in binary format, making it faster for both storage and retrieval.
   - The **readEmp()** function is used to read an employee's details from the binary file at a specific position.
   - The program checks for the employee's existence by searching the index file for a match and retrieving the record from the data file.

5. Add Employee:
   - When adding an employee, the program writes the record to the **data file** and updates the **index file** to map the employee ID to the position of the new record.
   - If the employee ID already exists, the program prevents adding a duplicate entry and prompts the user to try again.
   - The index file is kept sorted by employee ID to optimize search operations.

6. Search Employee:
   - The **searchEmployee()** function uses the index file to locate an employee's position and retrieves the record from the data file.
   - If the employee exists, the program displays their details. If not, it displays an error message.

7. Delete Employee:
   - To delete an employee, the program removes the employee record from the index file and marks the position as invalid.
   - It ensures the employee is present in the index file before attempting deletion.

8. Display All Employees:
   - The **display_all()** function iterates through the index file, retrieving the positions of all valid employee records from the data file and displays their details.

9. Menu-Driven Program:
   - The **main()** function provides a menu for the user to interact with the system:
     - Users can add, search, delete, or display all employee records.
     - The program uses a **do-while loop** to continuously prompt the user until they choose to exit.

10. Error Handling:
    - The program checks if the employee already exists before adding a new entry.
    - If the employee doesn't exist when searching or deleting, the system provides an appropriate message.

APPLICATIONS:
- This system can be used to manage employee records in organizations, where adding, searching, and deleting records is frequently required.
- Suitable for small to medium-sized organizations with a need for employee management using a file-based approach.

NOTE:
- **Indexing** is an important technique for optimizing search and retrieval operations in large files.
- **Binary files** are more efficient than text files for storing structured data like employee records.
- **Error handling** ensures that the program works reliably under various conditions.

IMPROVEMENT TIPS:
- **Memory Management**: Handle large data sets efficiently by optimizing the use of memory.
- **Error Handling**: More robust error handling (e.g., file access issues or invalid inputs) could be added.
- **Advanced Search**: Implementing a more advanced search algorithm or using a more complex data structure (like hash maps) could improve performance for larger datasets.
*/
