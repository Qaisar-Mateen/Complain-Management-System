#include "Employee.h"

Employee::Employee()
{
    id = -1;
}

Employee::Employee(int ID, string Name)
{
    id = ID;
    name = Name;
}

void Employee::control()
{
}

void Employee::printDetail()
{
    cout << "\n ID: " << id << "\t Name: " << name << "\n";
}

void Employee::updateSystem()
{

}

Employee::~Employee()
{
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
    int maxID = 0;
    int currentID;

    while (file >> currentID) {
        file.ignore(); // Ignore the space between ID and name
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

        if (currentID > maxID) {
            maxID = currentID;
        }
    }

    file.close();

    return maxID + 1;
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
