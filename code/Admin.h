#include <iostream>
#include<windows.h>
#include <string>
#include <vector>
#include "Person.h"
#include "Employee.h"
#include "Manager.h"
#include "Teacher.h"

using namespace std;

#ifndef _ADMIN_H
#define _ADMIN_H

class Admin : virtual public Person {
    int id;
    string Name;
    vector<Employee> Emps;
    vector<Manager> Managers;
    vector<Teacher> Teachs;

public:
    
    Admin();

    Admin(vector<Employee>, vector<Manager>, vector<Teacher>);

    int getID() const ;

    string getName() const;

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
};

#endif //_ADMIN_H