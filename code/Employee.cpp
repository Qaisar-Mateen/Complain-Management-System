#include "Employee.h"
#include "Department.h"
#include "Global.h"
#include <limits>

Employee::Employee()
{
    id = -1;
    name = "Invalid";
    Available = true;
}

Employee::Employee(int ID, string Name, bool aval)
{
    id = ID;
    name = Name;
    Available = aval;
}

void Employee::addDept(Department* d)
{
    if (dept)
        cout << "\n Employee already assigned to '" << dept->getName() << "' Department";
    else
        dept = d;
}

void Employee::addJob(Job* j) { 
    job.push_back(j); 
    if (!job.back()->isCompleted()) {
        Available = false;
    }
}

void Employee::control()
{
    char opt = 'd';
    while (opt != 'f')
    {
        opt = printInterface();

        if (opt == 'a') {
            system("cls");
            cout << "\t\t\t ----<><><><><><><><><><><><( Employee )><><><><><><><><><><><>----\n\n";
            cout << " ID: " << id << endl;
            cout << " Name: " << name << endl;
            cout << " Department: " << dept->getName() << "\n\n";
            if (job.empty()) cout << "\n No Jobs to Display\n";
            else {
                cout << "\n\t\t\t--<{ All Jobs Assigned }>--\n";
                for (int i = 0; i < job.size(); i++) job[i]->printDetail();
            }
        }

        else if (opt == 'b') updateSystem();

        if (opt != 'f' && opt != 'l') {
            cin.ignore();
            cout << "\n Press any key to continue...";
            cin.get();
        } 
    }
    cout << "\n Logging out...";
    Sleep(700);
    system("cls");
}


char Employee::printInterface() {
    bool valid = false;
    char opt;
    do {
        int b = 0;
        for (int i = 0; i < job.size(); i++)
            if (!job[i]->isCompleted()) b = 1;
        system("cls");
        cout << "\t\t\t ----<><><><><><><><><><><><( Employee )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << endl;
        cout << " Department: " << dept->getName() << "\n";
        cout << "\n --<{ Employee Controls }>--\n";
        cout << " a: View Assigned Jobs\n";
        if(b) cout << " b: Manage Active Job\n";
        cout << " f: Log Out\n";
        cout << " >";
        cin >> opt;

        if (opt == 'a' || (opt == 'b' && b) || opt == 'f')
            valid = true;

        else {
            cout << "\n Invalid!! \n";
            Sleep(700);
        }
    } while (!valid);
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

Employee::~Employee()
{
    dept->removeEmployee(this); //remove employee from dept frist
    Employee::markAsUnallocated(id);
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
    ifstream fileIn("Employee.txt");
    ofstream fileOut("Temp.txt");
    string line;

    while (getline(fileIn, line)) {
        if (!line.empty()) {
            istringstream iss(line);
            string field;
            getline(iss, field, ',');
            int empId = stoi(field);

            if (empId == id) {
                ostringstream oss;
                oss << id << ',';
                getline(iss, field, ',');  //name
                oss << field << ',';
                oss << (int)Available;
                line = oss.str();
            }
            fileOut << line << '\n';
        }
    }
    fileIn.close();
    fileOut.close();

    remove("Employee.txt");
    int chk = rename("Temp.txt", "Employee.txt");
}
