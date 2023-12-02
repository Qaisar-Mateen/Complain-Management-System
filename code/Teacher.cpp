#include "Teacher.h"
#define NOMINMAX
#include <windows.h>
#include "Complaint.h"
#include "Department.h"
#include "Global.h"

Teacher::Teacher()
{
	id = -1;
    name = "Invalid";
}

Teacher::Teacher(int ID, string Name)
{
	id = ID;
	name = Name;
}

void Teacher::control()
{
	char opt = 'd';

	while (opt != 'f')
	{
		opt = printInterface();

		if (opt == 'a')
			makeComplaint();

		else if (opt == 'b')
			complaintDetail();

		if (opt != 'f' && opt != 'l')
		{
			cin.ignore();
			cout << "\n Press any key to continue...";
			cin.get();
		}
	}
	cout << "\n Logging out...";
	Sleep(700);
	system("cls");
}

char Teacher::printInterface() {
	bool valid = false;
	char opt;
	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Teacher )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << name << endl;
		cout << "\n --<{ Teacher Controls }>--\n";
		cout << " a: Make a Complaint\n";
		cout << " b: Display Complaints\n";
		cout << " f: Log out\n";
		cout << " >";
		cin >> opt;

		if (opt == 'a' || opt == 'b' || opt == 'f')
			valid = true;
		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}

void Teacher::complaintDetail() {
	if (comps.empty()) {
		cout << "\n No Complaints to Display\n";
		return;
	}
	int opt;
	bool valid = false;
	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Teacher )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << name << "\n\n";
		cout << "\n\t\t\t--<{ All Complaints Detail }>--\n";
		for (int i = 0; i < comps.size(); i++)
			comps[i]->printDetail();

		cout << "\n\n Enter Complaint ID for Details: \n";
		cout << " 0: Go Back\n";
		cout << " >";
		cin >> opt;
		if (opt == 0)
			valid = true;
		Complaint* c = search(comps, opt);
		if (c) {
			valid = true;
			c->printFullDetail();
		}

		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}

	} while (!valid);
}

void Teacher::printDetail()
{
	cout << "\n ID: " << id << "\t Name: " << name << "\t Total Complaints Filed: " << comps.size() <<"\n";
}

void Teacher::makeComplaint() {
	string desc;
	int d_id;
	cout << "\n Enter Department ID for Complaint: ";
	cin >> d_id;
	if (!search(depts, d_id)) {
		cerr << "\n Invalid Department Id!!\n";
		return;
	}
	cin.ignore();
	cout << "\n Enter Complaint Description: ";
	getline(cin, desc);
	comps.push_back(new Complaint(desc, d_id, id));
	cout << "\n Complaint Filed successfully.\n";
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

int Teacher::getID() const {return id;}

string Teacher::getName() const {return name;}

void Teacher::addComplaint(Complaint* c) {comps.push_back(c);}

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
    int chk = rename("temp.txt", "Teacher.txt");
}