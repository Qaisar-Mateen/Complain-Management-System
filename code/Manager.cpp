#include "Manager.h"

Manager::Manager()
{
	id = -1;
}

Manager::Manager(int ID, string Name)
{
	id = ID;
	name = Name;
}

void Manager::printDetail()
{
	cout << "\n ID: "<< id <<"\t Name: " << name<<"\n";
}

void Manager::reviewRequest() {

}

void Manager::assignJob() {

}

void Manager::reviewJob() {

}

void Manager::writeToFile(const Manager& manage) {
    ofstream file("Manager.txt", ios::app);
    if (file.is_open()) {
        file << manage.getID() << " " << manage.getName() << endl;
        file.close();
    }
}

int Manager::getUniqueID() {
    ifstream file("Manager.txt");
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
int Manager::getID() const {
    return id;
}

string Manager::getName() const {
    return name;
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
    remove("Manager.txt");
    rename("temp.txt", "Manager.txt");
}