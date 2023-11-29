#pragma once

#include<string>
#include<vector>
//#include"Employee.h"
//#include"Complaint.h"
//#include"Manager.h"

using namespace std;

#ifndef _DEPARTMENT_H
#define _DEPARTMENT_H

class Employee;
class Manager;
class Complaint;

class Department {
    int id;
    string name;
    Manager* man;
    vector<Employee*> emps;
    vector<Complaint*> complaints;

public:
    Department(int ID, string Name, Manager* m);/* : id(ID), name(Name), man(m) {
        man->addDept(*this);
    }*/

    int getID();
    /*{
        return id;
    }*/

    string getName();
    /*{
        return name;
    }*/

    void addEmployee(Employee* e);
    /*{
        emps.push_back(e);
    }*/

    void addComplaint(Complaint* c);
    /*{
        complaints.push_back(c);
    }*/
};

#endif //_DEPARTMENT_H