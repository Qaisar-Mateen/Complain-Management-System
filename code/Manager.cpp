#include "Manager.h"
#include "Department.h"
#include "Employee.h"
#include "Global.h"
#include "Complaint.h"
#include "Job.h"

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

void Manager::addJob(Job* j) { job.push_back(j); }

void Manager::control()
{
    char opt = 'd';

    while (opt != 'f')
    {
        opt = printInterface();

        if (opt == 'a') reviewComplaint();

        else if (opt == 'b') viewNotif_E();

        else if (opt == 'c') {
            system("cls");
            cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
            cout << " ID: " << id << endl;
            cout << " Name: " << name << endl;
            cout << " Department: " << dept->getName() << "\n";
            dept->viewComplaint();
        }

        else if (opt == 'd') {
            system("cls");
            cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
            cout << " ID: " << id << endl;
            cout << " Name: " << name << endl;
            cout << " Department: " << dept->getName() << "\n";
            dept->pendingComplaint();
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
        int b = 0;
        for (auto it : job)
            if (it->isHighlight()) b = 1;
        system("cls");
        cout << "\t\t\t ----<><><><><><><><><><><><( Manager )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << endl;
        cout << " Department: " << dept->getName() << "\n";
        cout << "\n --<{ Manager Controls }>--\n";
        cout << " a: View New Complaints\n";
        if(b)
            cout << " b: View Notifications\n";
        cout << " c: View All Complaints\n";
        cout << " d: View Pending Complaints\n";
        cout << " f: Log Out\n";
        cout << " >";
        cin >> opt;

        if (opt == 'a' || (opt == 'b' && b) || opt == 'c' || opt == 'f' || opt == 'd')
            valid = true;

        else {
            cout << "\n Invalid!! \n";
            Sleep(700);
        }
    } while (!valid);
    return opt;
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

            dept->setCompState(opt, 1); //1 = assigned

            job.push_back(new Job(opt, this, assignEmp));

        }

        else {
            cout << "\n Invalid!! \n";
            Sleep(700);
        }
    } while (!valid);
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
    ::remove("Manager.txt");
    int chk = rename("temp.txt", "Manager.txt");
}