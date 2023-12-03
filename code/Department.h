#pragma once
#include<string>
#include<vector>

using namespace std;

#ifndef _DEPARTMENT_H
#define _DEPARTMENT_H

//class Manages {
//public:
//    virtual int getID() = 0;
//    virtual string getName() = 0;
//    virtual void printEmployees() = 0;
//    virtual vector<int> NewComplaint() = 0;
//    virtual vector<int> inDeptAndAval() = 0;
//    virtual void setCompState() = 0;
//};

class Employee;
class Manager;
class Complaint;

class Department/*: public Manages*/ {
public:
    int id;
    string name;
    Manager* man;
    vector<Employee*> emps;
    vector<Complaint*> complaints;

public:
    Department(int ID, string Name, Manager* m);

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

    vector<int> inDeptAndAval();

    void setCompState(int c_id, int st);
};

#endif //_DEPARTMENT_H