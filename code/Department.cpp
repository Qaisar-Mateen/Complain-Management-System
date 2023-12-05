#include "Department.h"
#include "Employee.h"
#include "Manager.h"
#include "Complaint.h"
#include "Global.h"

using namespace std;

Department::Department(int ID, string Name, Manager * m, vector<int> emp_id)
{
    id = ID;
    name = Name;
    man = m;
    man->addDept(this);
    for (int i = 0; i < emp_id.size(); i++) {
        Employee* e = search(emp, emp_id[i]);
        e->addDept(this);
        emps.push_back(e);
    }
}

int Department::getID()
{
    return id;
}

string Department::getName()
{
    return name;
}

void Department::printEmployees()
{
    cout << "\n\t\t\t--<{ Employees in Department }>--\n";
    for (int i = 0; i < emps.size(); i++)
        emps[i]->printDetail();
}

void Department::printDetail()
{
    cout << "\n ID: " << id << "\tName: " << name << "\tManager: " << man->getName() << "\tEmployees: ";
    for (int i = 0; i < emps.size(); i++)
        cout << emps[i]->getName() << ", ";
   cout << endl;
}

void Department::addEmployee(Employee* e)
{   
    emps.push_back(e);
}

void Department::changeManager(Manager* m)
{
    if (man)
        delete man;

    man = m;
    man->addDept(this);
    updateDept_file(id, -1, m->getID(), -1);
}

bool Department::removeEmployee(Employee* e)
{
    updateDept_file(id,e->getID(),-1, -1);
    if (!emps.empty())
    {
        auto it = find(emps.begin(), emps.end(), e);
        if (it != emps.end())
        {
            emps.erase(it);
            return true;
        }
    }
    return false;
}

bool Department::removeManager(Manager* m)
{
    if (man) {
        man = nullptr;
        return true;
    }
    return false;
}

void Department::addComplaint(Complaint* c)
{
    complaints.push_back(c);
}

vector<int> Department::NewComplaint() {
    vector<int> v;
    if(complaints.empty()) {
        cout << "\n No Complaints to Display\n";
        return v;
    }
    cout << "\n\t\t\t--<{ UnAssigned Complaints Detail }>--\n";
    for (int i = 0; i < complaints.size(); i++)
        if (complaints[i]->getState() == State::New) {
            complaints[i]->printDetail();
            v.push_back(complaints[i]->getID());
        }
    return v;
}

void Department::pendingComplaint() {
    if (complaints.empty()) {
        cout << "\n No Complaints to Display\n";
        return;
    }
    cout << "\n\t\t\t--<{ Pending Complaints Detail }>--\n";
    for (int i = 0; i < complaints.size(); i++)
        if (complaints[i]->getState() != State::Resolved && complaints[i]->getState() != State::Closed) complaints[i]->printDetail();
}

void Department::viewComplaint() {
    if (complaints.empty()) {
        cout << "\n No Complaints to Display\n";
        return;
    }
    cout << "\n\t\t\t--<{ All Complaints Detail }>--\n";
    for (int i = 0; i < complaints.size(); i++)
        complaints[i]->printDetail();
}

vector<int> Department::inDeptAndAval() {
    vector<int> v;
    for (auto it : emps)
        if (it->isAvailable())
            v.push_back(it->getID());

    return v;
}

void Department::setCompState(int c_id, int st) {
    State s = State::New;
    switch (st) {
    case 0: s = State::New; break;
    case 1: s = State::Assigned; break;
    case 2: s = State::Resolved; break;
    case 3: s = State::Closed;
    }
    for (int i = 0; i < complaints.size(); i++)
        if (complaints[i]->getID() == c_id) complaints[i]->setState(s);
}

void Department::updateDept_file(int deptId, int emp_rem_id = -1, int man_id = -1, int emp_add_id = -1) {
    ifstream fileIn("Department.txt");
    ofstream fileOut("Temp.txt");
    string line;

    while (getline(fileIn, line)) {
        istringstream iss(line);
        string field;

        getline(iss, field, ' ');
        int id = stoi(field);

        if (id == deptId) {
            ostringstream oss;
            oss << deptId << ' ';
            getline(iss, field, '\'');  // dept name
            oss << field << "' ";
            iss.get();
            if (man_id == -1) {
                getline(iss, field, ' ');  // managerId
                oss << field << ' ';
            }
            else {
                getline(iss, field, ' ');  // replace manager
                oss << man_id << ' ';
            }

            iss.get();
            vector<int> empIds;
            while (iss >> field) {
                int emp = stoi(field);
                if (emp != emp_rem_id) empIds.push_back(emp);
            }

            oss << '"';
            for (size_t i = 0; i < empIds.size(); ++i) {
                if (i > 0) oss << ' ';
                oss << empIds[i];
            }
            oss << '"';
            line = oss.str();
        }
        fileOut << line << '\n';
    }

    fileIn.close();
    fileOut.close();
    remove("Department.txt");
    int chk = rename("Temp.txt", "Department.txt");
}