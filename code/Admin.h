#include <iostream>
#include <string>
#include <vector>
#include "Employee.h"
#include "Manager.h"
#include "Teacher.h"

using namespace std;

#ifndef _ADMIN_H
#define _ADMIN_H

class Admin {
    int id;
    string Name;
    vector<Employee> Emps;
    vector<Manager> Managers;
    vector<Teacher> Teachs;


public:
    
    Admin();

    Admin(vector<Employee>, vector<Manager>, vector<Teacher>);

    void displayEmployees();

    void displayManagers();

    void displayTeachers();

    void addEmployee();
    
    void addManager();
        
    void addTeacher();
    
    void removeEmployee();
    
    void removeTeacher();
    
    void removeManager();
};

#endif //_ADMIN_H