#include "Teacher.h"

Teacher::Teacher()
{
	id = -1;
}

Teacher::Teacher(int ID, string Name)
{
	id = ID;
	name = Name;
}

void Teacher::control()
{
}

void Teacher::printDetail()
{
	cout << "\n ID: " << id << "\t Name: " << name << "\n";
}

void Teacher::makeComplain() {

}

void Teacher::printComplains() {

}

void Teacher::reocordFeedback() {

}

void Teacher::writeToFile(const Teacher& teach) {
    ofstream file("Teacher.txt", ios::app);
    if (file.is_open()) {
        file << teach.getID() << " " << teach.getName() << endl;
        file.close();
    }
}

int Teacher::getUniqueID() {
    ifstream file("Teacher.txt");
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
int Teacher::getID() const {
    return id;
}

string Teacher::getName() const {
    return name;
}

void Teacher::addComplaint(Complaint* c)
{
    comps.push_back(c);
}

void Teacher::markAsUnallocated(int teachId) {
    ifstream inFile("Teacher.txt");
    ofstream outFile("temp.txt");

    int currentID;
    string currentName;

    while (inFile >> currentID) {
        inFile.ignore(); // Ignore the space between ID and name
        getline(inFile, currentName); // Read the rest of the line, including spaces

        if (currentID == teachId) {
            // Unallocate Id
            outFile << "";
            cout << "\n Teacher with ID " << teachId << " removed successfully.\n";
        }
        else {
            outFile << currentID << " " << currentName << endl;
        }
    }

    inFile.close();
    outFile.close();

    // Rename the temp file to replace the original file
    remove("Teacher.txt");
    rename("temp.txt", "Teacher.txt");
}