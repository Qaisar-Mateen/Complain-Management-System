#include "Manager.h"
#include "Department.h"
#include "Global.h"

Manager::Manager()
{
	id = -1;
    name = "Invalid";
    dept = nullptr;
}

Manager::Manager(int ID, string Name)
{
	id = ID;
	name = Name;
    dept = nullptr;
}

void Manager::addDept(Department* d)
{
    if (dept)
        cout << "\n Already Manager of Dept: " << dept->getName();
    else
        dept = d;
}

void Manager::control()
{
    char opt = 'd';

    while (opt != 'f')
    {
        opt = printInterface();

        if (opt == 'a') {
            
        }

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

char Manager::printInterface() {
    bool valid = false;
    char opt;
    do {
        system("cls");
        cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << endl;
        cout << "\n --<{ Manager Controls }>--\n";
        cout << " a: View New Complaints\n";
        cout << " b: \n";
        cout << " f: Log Out\n";
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

void Manager::printDetail()
{
    cout << "\n ID: " << id << "\tName: " << name << "\tDepartment: " << dept->getName() << "\n";
}

void Manager::reviewComplaint() {
    bool valid = false;
    int opt;
    do {
        system("cls");
        cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << "\n\n";
        vector<int> v = dept->NewComplaint();
        if (v.empty())
            return;
       
        cout << "\n\n Enter ID of Complaint to Assign: \n";
        cout << " 0: Go Back\n";
        cout << " >";
        cin >> opt;
        if (opt == 0)
            valid = true;

        for (int i = 0; i < v.size(); i++)
            if (v[i] == opt)
                valid = true;

        if (valid) {
            //Complaint* c = search(coms, opt);
        }

        else {
            cout << "\n Invalid!! \n";
            Sleep(700);
        }
    } while (!valid);
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
    int maxID = 1;
    int currentID;

    while (file >> currentID) {
        file.ignore(); // Ignore the space between ID and name
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

        if (currentID == maxID)
            maxID++;
    }
    file.close();

    return maxID;
}
int Manager::getID() const {
    return id;
}

int Manager::getDeptId()
{
    return dept->getID();
}

string Manager::getName() const {
    return name;
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
    remove("Manager.txt");
    int chk = rename("temp.txt", "Manager.txt");
}