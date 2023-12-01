#include "Department.h"
#include "Employee.h"
#include "Manager.h"
#include "Complaint.h"

using namespace std;

Department::Department(int ID, string Name, Manager * m)//, vector<int> v)
{
    id = ID;
    name = Name;
    man = m;
    man->addDept(this);
}

int Department::getID()
{
    return id;
}

string Department::getName()
{
    return name;
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
}


bool Department::removeEmployee(Employee* e)
{
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