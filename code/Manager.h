#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Person.h"
#include "Department.h"
using namespace std;

//class Department;

#ifndef _MANAGER_H
#define _MANAGER_H

class Job;

class Manager : virtual public Person {
private:
    int id;
    string name;
    Manages* dept;
    vector<Job*> job;
public: 
    Manager(int ID, string Name);

    void addDept(Department* d);

    void addJob(Job* j);

    void control();

    void printDetail();

    static void writeToFile(const Manager& manage);

    static int getUniqueID();

    int getID() const;

    int getDeptId();

    string getName() const;

    static void markAsUnallocated(int manageId);

    ~Manager();
private:
    char printInterface();
    void viewNotif_E();
    void reviewComplaint();
    Manager();
};

#endif //_MANAGER_H