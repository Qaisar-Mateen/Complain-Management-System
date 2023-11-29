#include <string>
#include <iostream>
#include <fstream>
#include "Person.h"
using namespace std;

#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

class Department;

class Employee: virtual public Person {
    int id;
    string name;
    Department* dept;

public:
    Employee();

    Employee(int ID, string Name);

    void control();

    static void writeToFile(const Employee& emp);

    static int getUniqueID();

    int getID() const;

    string getName() const;

    void printDetail();

    void updateSystem();

    static void markAsUnallocated(int empId);
};

#endif //_EMPLOYEE_H