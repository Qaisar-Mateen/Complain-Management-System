#include <string>
#include <iostream>
#include <fstream>
#include "Person.h"
#include "Job.h"
using namespace std;

#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

class Department;
class WorksIn;

class Employee: virtual public Person {
    int id;
    string name;
    WorksIn* dept;
    vector<Job*> job;
    bool Available;

public:
    Employee();

    Employee(int ID, string Name);

    void addDept(Department *d);

    void addJob(Job* j);

    void control();

    char printInterface();

    static void writeToFile(const Employee& emp);

    static int getUniqueID();

    int getID() const;

    string getName() const;

    bool isAvailable();

    void printDetail();

    void updateSystem();

    ~Employee();

    static void markAsUnallocated(int empId);
};

#endif //_EMPLOYEE_H