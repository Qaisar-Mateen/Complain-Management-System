#include "Employe.h"

Employe::Employe()
{
    id = -1;
}

Employe::Employe(int ID, string Name)
{
    id = ID;
    name = Name;
}

void Employe::printDetail()
{
    cout << "\n ID: " << id << "\t Name: " << name << "\n";
}

void Employe::updateSystem()
{

}

Employe::~Employe()
{
}
int Employe::getID() const {
    return id;
}

string Employe::getName() const {
    return name;
}

void Employe::writeToFile(const Employe& emp) {
    ofstream file("Employee.txt", ios::app);
    if (file.is_open()) {
        file << emp.getID() << " " << emp.getName() << endl;
        file.close();
    }
}

int Employe::getUniqueID() {
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

void Employe::markAsUnallocated(int empId) {
    ifstream inFile("Employee.txt");
    ofstream outFile("temp.txt");

    int currentID;
    string currentName;

    while (inFile >> currentID >> currentName) {
        if (currentID == empId) {
            // Unallocate Id
            outFile << "" << "";
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