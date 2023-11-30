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

    /*for(int i = 0; i < v.size(); i++)
    {
    }*/

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
    cout << "\n ID: " << id << "\tName: " << name << "\tManager: " << man->getName() << " Employees ";
    for (int i = 0; i < emps.size(); i++)
        cout << emps[i]->getName() << ", ";
   cout << endl;
}

void Department::addEmployee(Employee* e)
{   
    emps.push_back(e);
}

void Department::addComplaint(Complaint* c)
{
    complaints.push_back(c);
}