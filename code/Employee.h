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
    Employee(int ID, string Name, bool aval);

    int getID() const;

    string getName() const;

    void setAvailable(bool t);

    void addDept(Department *d);

    void addJob(Job* j);

    void control();

    bool isAvailable();

    void printDetail();

    static void writeToFile(const Employee& emp);

    static void markAsUnallocated(int empId);

    static int getUniqueID();

    ~Employee();
private:
    void updateFile();
    char printInterface();
    void updateSystem();
    Employee();
};

#endif //_EMPLOYEE_H