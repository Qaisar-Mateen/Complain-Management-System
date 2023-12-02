#pragma once
#include<string>
#include<vector>

using namespace std;

#ifndef _DEPARTMENT_H
#define _DEPARTMENT_H

class Employee;
class Manager;
class Complaint;

class Department {
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

    void printDetail();
   
    void addEmployee(Employee* e);

    void changeManager(Manager* m);

    bool removeEmployee(Employee* e);

    bool removeManager(Manager* m);
    
    void addComplaint(Complaint* c);

    vector<int> NewComplaint();

    bool inDept(int id);
};

#endif //_DEPARTMENT_H