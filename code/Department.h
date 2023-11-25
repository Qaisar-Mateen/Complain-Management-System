#include<string>
#include<vector>
#include"Manager.h"
#include"Employee.h"
#include"Complaint.h"

using namespace std;

#ifndef _DEPARTMENT_H
#define _DEPARTMENT_H

class Department {
    int id;
    string name;
    Manager* man;
    vector<Employee*> emps;
    vector<Complaint*> complaints;

public:
    Department(int ID, string Name, Manager* m)
    {
        id = ID;
        name = Name;
        man = m;
    }

    void addEmployee(Employee* e)
    {
        emps.push_back(e);
    }

    void addManager(Manager* m)
    {
        if (man != nullptr)
            delete man;
        man = m;        
    }

    void addComplaint(Complaint* c)
    {
        complaints.push_back(c);
    }
};

#endif //_DEPARTMENT_H