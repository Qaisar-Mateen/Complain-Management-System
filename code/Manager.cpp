#include "Manager.h"
#include "Department.h"
#include "Employee.h"
#include "Global.h"
#include "Complaint.h"
#include "Job.h"

// Default constructor for the Manager class
Manager::Manager()
{
    id = -1; // Initialize the ID to -1
    name = "Invalid"; // Initialize the name to "Invalid"
    dept = nullptr; // Initialize the department pointer to nullptr
}

// Parameterized constructor for the Manager class
Manager::Manager(int ID, string Name)
{
    id = ID; // Set the ID to the passed value
    name = Name; // Set the name to the passed value
    dept = nullptr; // Initialize the department pointer to nullptr
}

// Function to add a department to the manager
void Manager::addDept(Department* d)
{
    if (dept) // If the manager already has a department
        cout << "\n Already Manager of Dept: " << dept->getName(); // Print a message
    else
        dept = d; // Otherwise, set the department to the passed value
}

// Function to add a job to the manager
void Manager::addJob(Job* j) { job.push_back(j); } // Add the job to the list of jobs

// Function to control the manager's actions
void Manager::control()
{
    char opt = 'd'; // Initialize the option to 'd'

    // Loop until the option is 'f'
    while (opt != 'f')
    {
        opt = printInterface(); // Print the interface and get the user's option

        if (opt == 'a') reviewComplaint(); // If the option is 'a', review the complaint

        else if (opt == 'b') viewNotif_E(); // If the option is 'b', view the notifications

        else if (opt == 'c') { // If the option is 'c', view the department's complaints
            system("cls"); // Clear the console
            cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
            cout << " ID: " << id << endl;
            cout << " Name: " << name << endl;
            cout << " Department: " << dept->getName() << "\n";
            dept->viewComplaint();
        }

        else if (opt == 'd') { // If the option is 'd', view the department's pending complaints
            system("cls"); // Clear the console
            cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
            cout << " ID: " << id << endl;
            cout << " Name: " << name << endl;
            cout << " Department: " << dept->getName() << "\n";
            dept->pendingComplaint();
        }

        if (opt != 'f' && opt != 'l') // If the option is not 'f' or 'l'
        {
            cin.ignore(); // Ignore the newline character in the input buffer
            cout << "\n Press any key to continue..."; // Print a message
            cin.get(); // Wait for the user to press a key
        }
    }
    cout << "\n Logging out..."; // Print a message
    Sleep(700); // Pause for 700 milliseconds
    system("cls"); // Clear the console
}


// Function to print the manager's interface and get the user's option
char Manager::printInterface() {
    bool valid = false; // Initialize the valid flag to false
    char opt; // Declare a variable to hold the user's option
    do {
        int b = 0; // Initialize a flag to 0
        for (auto it : job) // For each job
            if (it->isHighlight()) b = 1; // If the job is highlighted, set the flag to 1
        vector<int> v = dept->NewComplaint(); // Get the new complaints
        system("cls"); // Clear the console
        cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << endl;
        cout << " Department: " << dept->getName() << "\n";
        cout << "\n --<{ Manager Controls }>--\n";
        if (!v.empty()) cout << " a: View New Complaints\n"; // If there are new complaints, print the option to view them
        if (b) cout << " b: View Notifications\n"; // If there are highlighted jobs, print the option to view notifications
        cout << " c: View All Complaints\n"; // Print the option to view all complaints
        cout << " d: View Pending Complaints\n"; // Print the option to view pending complaints
        cout << " f: Log Out\n"; // Print the option to log out
        cout << " >";
        cin >> opt; // Get the user's option

        // If the option is valid, set the valid flag to true
        if ((opt == 'a' && !v.empty()) || (opt == 'b' && b) || opt == 'c' || opt == 'f' || opt == 'd')
            valid = true;

        else { // If the option is not valid
            cout << "\n Invalid!! \n"; // Print a message
            Sleep(700); // Pause for 700 milliseconds
        }
    } while (!valid); // Repeat until the option is valid
    return opt; // Return the user's option
}

void Manager::viewNotif_E() {
    bool valid = false;
    int opt;
    do {
        vector<int> v;
        system("cls");
        cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << endl;
        cout << " Department: " << dept->getName() << "\n\n";
        cout << "\n\t\t\t--<{ Notification from Employees }>--\n";
        for (int i = 0; i < job.size(); i++)
            if (job[i]->isHighlight()) { job[i]->printDetail(); v.push_back(job[i]->getID()); }

        if (v.empty()) { 
            cout << "\n No Notification From Employees\n"; 
            valid = true;
        }
        else {
            cout << "\n\n Enter ID: \n";
            cout << " 0: Go Back\n";
            cout << " >";
            cin >> opt;
            int val = 0;

            for (int i = 0; i < v.size(); i++)
                if (v[i] == opt) val = 1;

                if (opt == 0) valid = true;

                else if (val) {
                    valid = true;
                    bool valid2 = false;
                    do {
                        char op;
                        cout << " a: Accept\n";
                        cout << " r: Reject\n";
                        cout << " l: Go Back\n >";
                        cin >> op;
                        if (op == 'l') valid2 = true;

                        else if (op == 'a') {
                            valid2 = true;
                            for (int i = 0; i < job.size(); i++)
                                if (job[i]->getID() == opt) {
                                    job[i]->read();
                                    int c_id = job[i]->getComID();
                                    search(coms, c_id)->setNotifyTea(true);
                                }
                        }
                            
                        else if (op == 'r') {
                            valid2 = true;
                            for (int i = 0; i < job.size(); i++)
                                if (job[i]->getID() == opt) {
                                    job[i]->Complete(false);
                                    int c_id = job[i]->getComID();
                                    Complaint* c = search(coms, c_id);
                                    dept->setCompState(c_id, 1);
                                }
                        }

                    } while (!valid2);
                }

                else {
                    cout << "\n Invalid!! \n";
                    Sleep(700);
                }
        }
    } while (!valid);
}


void Manager::printDetail()
{
    cout << "\n ID: " << id << "\t Name: " << name << "\t Department: " << dept->getName() << "\n";
}

void Manager::reviewComplaint() {
    bool valid = false;
    int opt;
    do {
        system("cls");
        cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << "\n";
        cout << " Department: " << dept->getName() << "\n\n";
        vector<int> v = dept->NewComplaint();
        if (v.empty()) {
            cout << "\n No New Complaints to Display\n";
            return;
        }
       
        cout << "\n\n Enter ID of Complaint to Assign: \n";
        cout << " 0: Go Back\n";
        cout << " >";
        cin >> opt;
        for (int i = 0; i < v.size(); i++)
            if (v[i] == opt)
                valid = true;

        if (opt == 0)
            valid = true;

        else if (valid) {
            dept->printEmployees();
            int e_Id = -1, exists = 0;
            vector<int> assignEmp, aval = dept->inDeptAndAval();
            cout << "\n Enter IDs of Employees to Assign Job (enter 0 when done): \n";
            while (e_Id != 0) {
                cout << " >";
                cin >> e_Id;
                if (e_Id == -1) break;
                for (int i = 0; i < aval.size(); i++)
                    if (e_Id == aval[i]) exists = 1;

                if (e_Id == 0 && assignEmp.empty()) { cerr << "\n Minimum One Employee Needed!!\n"; e_Id = -1; }

                else if (e_Id == 0) break;

                else if (!exists)
                    cerr << "\n ERROR: Employee is Not in "<< dept->getName() << " Dept or is Not Avaliable\n";

                else if (e_Id != 0) assignEmp.push_back(e_Id);
            }
            if (e_Id != -1) {
                dept->setCompState(opt, 1); //1 = assigned
                job.push_back(new Job(opt, this, assignEmp));
                cout << "\n Job Assigned to Employees\n";
            }
        }

        else {
            cout << "\n Invalid!! \n";
            Sleep(700);
        }
    } while (!valid);
}

// Function to write the manager's details to a file
void Manager::writeToFile(const Manager& manage) {
    ofstream file("Manager.txt", ios::app); // Open the file in append mode
    if (file.is_open()) { // If the file is open
        file << manage.getID() << " " << manage.getName() << endl; // Write the manager's ID and name
        file.close(); // Close the file
    }
}

// Function to get a unique ID for a new manager
int Manager::getUniqueID() {
    ifstream file("Manager.txt"); // Open the file
    int maxID = 1; // Initialize the maximum ID to 1
    int currentID; // Declare a variable to hold the current ID

    // While there are more IDs in the file
    while (file >> currentID) {
        file.ignore(); // Ignore the space between the ID and name
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

        if (currentID == maxID) // If the current ID is equal to the maximum ID
            maxID++; // Increment the maximum ID
    }
    file.close(); // Close the file

    return maxID; // Return the maximum ID
}

// Function to get the manager's ID
int Manager::getID() const {
    return id; // Return the ID
}

// Function to get the manager's department's ID
int Manager::getDeptId() {
    return dept->getID(); // Return the department's ID
}

// Function to get the manager's name
string Manager::getName() const {
    return name; // Return the name
}

Manager::~Manager()
{
    dept->removeManager(this);
    Manager::markAsUnallocated(id);   

    if (search(man, id))
    {
        for (auto it = man.begin(); it != man.end(); ++it)
            if ((*it)->getID() == id)
                it = man.erase(it);
    }
}

void Manager::markAsUnallocated(int manageId) {
    ifstream inFile("Manager.txt");
    ofstream outFile("temp.txt");

    int currentID;
    string currentName;

    while (inFile >> currentID) {
        inFile.ignore(); // Ignore the space between ID and name
        getline(inFile, currentName); // Read the rest of the line, including spaces

        if (currentID == manageId) {
            // Unallocate Id
            outFile << "" ;
            cout << "\n Manager with ID " << manageId << " removed successfully.\n";
        }
        else {
            outFile << currentID << " " << currentName << endl;
        }
    }

    inFile.close();
    outFile.close();

    // Rename the temp file to replace the original file
    ::remove("Manager.txt");
    int chk = rename("temp.txt", "Manager.txt");
}