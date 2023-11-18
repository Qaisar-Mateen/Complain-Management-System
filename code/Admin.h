#include <iostream>
#include <string>
#include <vector>
#include "Employe.h"
#include "Manager.h"
#include "Teacher.h"

using namespace std;

#ifndef _ADMIN_H
#define _ADMIN_H

class Admin {
    int id;
    string Name;
    vector<Employe> Emps;
    vector<Manager> Managers;
    vector<Teacher> Teachs;


public:
    
    Admin();

    Admin(vector<Employe>, vector<Manager>, vector<Teacher>);

    void displayEmployes();

    void displayManagers();

    void displayTeachers();

    void addEmploye();
    
    void addManager();
        
    void addTeacher();
    
    void removeEmploye();
    
    void removeTeacher();
    
    void removeManager();
};

#endif //_ADMIN_H