#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include "Person.h"



using namespace std;

#ifndef _ADMIN_H
#define _ADMIN_H

class Employee;
class Manager;
class Teacher;

class Admin : virtual public Person {
    int id;
    string Name;
    vector<Employee*> *Emps;
    vector<Manager*> *Managers;
    vector<Teacher*> *Teachs;

public:
    
    Admin();

    Admin(vector<Employee*>&, vector<Manager*>&, vector<Teacher*>&);

    int getID() const;

    string getName() const;

    char printInterface();

    char printAddInterface();

    char printRemoveInterface();

    char printDetailInterface();

    void control();

    void displayEmployees();

    void displayManagers();

    void displayTeachers();

    void addEmployee();
    
    void addManager();
        
    void addTeacher();
    
    void removeEmployee();
    
    void removeTeacher();
    
    void removeManager();

    bool emp_delete(int Id);

    bool man_delete(int Id);

    bool tea_delete(int Id);
};

#endif //_ADMIN_H