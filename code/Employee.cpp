#include "Employee.h"
#include "Department.h"
#include "Global.h"
#include <limits>

// Default constructor for Employee
Employee::Employee()
{
    id = -1; // Initialize id to -1
    name = "Invalid"; // Initialize name to "Invalid"
    Available = true; // Initialize Available to true
}

// Parameterized constructor for Employee
Employee::Employee(int ID, string Name, bool aval)
{
    id = ID; // Set id to the provided ID
    name = Name; // Set name to the provided Name
    Available = aval; // Set Available to the provided availability status
}

// Function to add a Department to the Employee
void Employee::addDept(Department* d)
{
    // If the Employee is already assigned to a Department, print a message
    if (dept)
        cout << "\n Employee already assigned to '" << dept->getName() << "' Department";
    // Otherwise, assign the provided Department to the Employee
    else
        dept = d;
}

// Function to add a Job to the Employee
void Employee::addJob(Job* j) {
    job.push_back(j); // Add the provided Job to the Employee's job list
    // If the added Job is not completed, set Available to false
    if (!job.back()->isCompleted()) {
        Available = false;
    }
}

// Function that controls the Employee module
void Employee::control()
{
    char opt = 'd';

    // Keep running until the user chooses to log out
    while (opt != 'f')
    {
        // Print the main interface and get the user's option
        opt = printInterface();

        // If the user chooses to view details
        if (opt == 'a') {
            // Clear the console
            system("cls");
            // Print the Employee's details
            cout << "\t\t\t ----<><><><><><><><><><><><( Employee )><><><><><><><><><><><>----\n\n";
            cout << " ID: " << id << endl;
            cout << " Name: " << name << endl;
            cout << " Department: " << dept->getName() << "\n\n";
            // If the Employee has no jobs, print a message
            if (job.empty()) cout << "\n No Jobs to Display\n";
            // Otherwise, print the details of all jobs
            else {
                cout << "\n\t\t\t--<{ All Jobs Assigned }>--\n";
                for (int i = 0; i < job.size(); i++) job[i]->printDetail();
            }
        }

        // If the user chooses to update the system
        else if (opt == 'b') updateSystem();

        // If the user doesn't choose to log out or go back, wait for the user to press a key before continuing
        if (opt != 'f' && opt != 'l') {
            cin.ignore();
            cout << "\n Press any key to continue...";
            cin.get();
        }
    }
    // Log out
    cout << "\n Logging out...";
    Sleep(700);
    system("cls");
}

// Function to print the Employee's interface and get the user's option
char Employee::printInterface() {
    bool valid = false;
    char opt;
    do {
        int b = 0;
        // Check if there are any incomplete jobs
        for (int i = 0; i < job.size(); i++)
            if (!job[i]->isCompleted()) b = 1;
        // Clear the console
        system("cls");
        // Print the Employee's details
        cout << "\t\t\t ----<><><><><><><><><><><><( Employee )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << endl;
        cout << " Department: " << dept->getName() << "\n";
        // Print the available options
        cout << "\n --<{ Employee Controls }>--\n";
        cout << " a: View Assigned Jobs\n";
        // If there are any incomplete jobs, print the option to manage them
        if (b) cout << " b: Manage Active Job\n";
        cout << " f: Log Out\n";
        cout << " >";
        // Get the user's option
        cin >> opt;

        // Validate the user's option
        if (opt == 'a' || (opt == 'b' && b) || opt == 'f')
            valid = true;
        else {
            // Print an error message if the user's option is invalid
            cout << "\n Invalid!! \n";
            Sleep(700);
        }
    } while (!valid);
    // Return the user's option
    return opt;
}
void Employee::printDetail()
{
    cout << "\n ID: " << id << "\tName: " << name << "\tDepartment: " << dept->getName() << ((Available) ? "\t Available " : "\t Not Available") << "\n";
}

void Employee::updateSystem() {
    bool valid = false;
    char opt;
    do {
        system("cls");
        cout << "\t\t\t ----<><><><><><><><><><><><( Employee )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << endl;
        cout << " Department: " << dept->getName() << "\n\n";
        cout << "\n\t\t\t--<{ Active Job }>--\n";
        int c_id = 0, cur = 0;
        for (int i = 0; i < job.size(); i++)
            if (!job[i]->isCompleted()) {
                job[i]->printDetail();
                c_id = job[i]->getID();
                cur = i;
            }
        cout << "\n a: Mark as Complete\n";
        cout << " l: Go Back\n";
        cout << " >";
        cin >> opt;

        if (opt == 'l')
            valid = true;

        else if (opt == 'a') {
            job[cur]->Complete(true);
            dept->setCompState(c_id, 2); // 2 = resolved
            valid = true;
            cout << "\n Job Completed successfully\n";
        }

        else {
            cout << "\n Invalid!! \n";
            Sleep(700);
        }
    } while (!valid);
}

void Employee::setAvailable(bool t) { Available = t; updateFile(); }

//constructor for proper deletion of object
Employee::~Employee()
{
    dept->removeEmployee(this); //remove employee from dept frist
    Employee::markAsUnallocated(id);
    for (auto it : job)
        it->removeEmp(this);
}

int Employee::getID() const {
    return id;
}

string Employee::getName() const {
    return name;
}

bool Employee::isAvailable() { return Available; }

void Employee::writeToFile(const Employee& emp) {
    ofstream file("Employee.txt", ios::app);
    if (file.is_open()) {
        file << emp.getID() << "," << emp.getName() << "," << (int)emp.Available << endl;
        file.close();
    }
}

int Employee::getUniqueID() {
    ifstream file("Employee.txt");
    int maxID = 1;
    int currentID;

    while (file >> currentID) {
        file.ignore(); // Ignore the space between ID and name
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

        if (currentID == maxID) {
            maxID++;
        }
    }
    file.close();

    return maxID;
}

void Employee::markAsUnallocated(int empId) {
    ifstream inFile("Employee.txt");
    ofstream outFile("temp.txt");

    int currentID;
    string currentName;

    while (inFile >> currentID) {
        inFile.ignore(); // Ignore the space between ID and name
        getline(inFile, currentName); // Read the rest of the line, including spaces

        if (currentID == empId) {
            // Unallocate Id
            outFile << "" ;

            cout << "\n Employee with ID " << empId << " removed successfully.\n";
        }
        else {
            outFile << currentID << " " << currentName << endl;
        }
    }

    inFile.close();
    outFile.close();

    // Rename the temp file to replace the original file
    remove("Employee.txt");
    int chk = rename("temp.txt", "Employee.txt");
}

void Employee::updateFile() {
    ifstream fileIn("Employee.txt");  // Open the existing employee file for reading
    ofstream fileOut("Temp.txt");  // Open a temporary file for writing
    string line;

    while (getline(fileIn, line)) {  // Read the file line by line
        if (!line.empty()) {
            istringstream iss(line);
            string field;
            getline(iss, field, ',');
            int empId = stoi(field);

            if (empId == id) {  // If the employee ID matches the current employee's ID
                ostringstream oss;
                oss << id << ',';
                getline(iss, field, ',');  // Read the name
                oss << field << ',';
                oss << (int)Available;  
                line = oss.str();  // Update the line with the new details
            }
            fileOut << line << '\n';  // Write the line to the temporary file
        }
    }
    fileIn.close();  
    fileOut.close();  
    remove("Employee.txt");  // Delete the original file
    int chk = rename("Temp.txt", "Employee.txt");  // Rename the temporary file to the original file name
}