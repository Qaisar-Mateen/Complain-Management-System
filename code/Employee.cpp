#include "Employee.h"
#include "Department.h"
#include "Global.h"
#include <limits>

Employee::Employee()
{
    id = -1;
    name = "Invalid";
}

Employee::Employee(int ID, string Name)
{
    id = ID;
    name = Name;
}

void Employee::addDept(Department* d)
{
    if (dept)
        cout << "\n Employee already assigned to '" << dept->getName() << "' Department";
    else
        dept = d;
}

void Employee::control()
{
}

void Employee::printDetail()
{
    cout << "\n ID: " << id << "\tName: " << name << "\tDepartment: " << dept->getName() <<"\n";
}

void Employee::updateSystem()
{

}

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

void Employee::writeToFile(const Employee& emp) {
    ofstream file("Employee.txt", ios::app);
    if (file.is_open()) {
        file << emp.getID() << " " << emp.getName() << endl;
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
    rename("temp.txt", "Employee.txt");
}

