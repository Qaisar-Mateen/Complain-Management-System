#pragma once
#include<string>
#include<vector>
#include <fstream>
#include <sstream>
#include "Date.h"

using namespace std;

#ifndef _DEPARTMENT_H
#define _DEPARTMENT_H

class Employee;
class Manager;
class Complaint;

class Manages {
public:
    virtual int getID() = 0;
    virtual string getName() = 0;
    virtual void printEmployees() = 0;
    virtual vector<int> NewComplaint() = 0;
    virtual vector<int> inDeptAndAval() = 0;
    virtual void setCompState(int c_id, int st) = 0;
    virtual bool removeManager(Manager* m) = 0;
    virtual void pendingComplaint() = 0;
    virtual void viewComplaint() = 0;
};

class WorksIn {
public:
    virtual int getID() = 0;
    virtual string getName() = 0;
    virtual void setCompState(int c_id, int st) = 0;
    virtual bool removeEmployee(Employee* e) = 0;
};

class Reports {
public:
    virtual void summary(Date st, Date end) = 0;
};

class Department: public Manages, public WorksIn, public Reports {
public:
    int id;
    string name;
    Manager* man;
    vector<Employee*> emps;
    vector<Complaint*> complaints;

public:
    Department(int ID, string Name, Manager* m, vector<int> emp_id);

    int getID();
   
    string getName();

    void printEmployees();

    void printDetail();
   
    void addEmployee(Employee* e);

    void changeManager(Manager* m);

    bool removeEmployee(Employee* e);

    bool removeManager(Manager* m);
    
    void addComplaint(Complaint* c);

    vector<int> NewComplaint();

    void pendingComplaint();

    void viewComplaint();

    vector<int> inDeptAndAval();

    void setCompState(int c_id, int st);

    void summary(Date st, Date end);
private:
    void updateDept_file(int deptId, int emp_rem_id, int man_id, int emp_add_id);
};

#endif //_DEPARTMENT_H