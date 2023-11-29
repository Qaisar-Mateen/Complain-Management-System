#include "Department.h"
#include "Employee.h"
#include "Manager.h"
#include "Complaint.h"

using namespace std;

Department::Department(int ID, string Name, Manager * m) 
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

void Department::addEmployee(Employee* e)
{
    emps.push_back(e);
}

void Department::addComplaint(Complaint* c)
{
    complaints.push_back(c);
}