#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef _MANAGER_H
#define _MANAGER_H

class Manager {
private:
    int id;
    string name;

public: 
    Manager();

    Manager(int ID, string Name);

    void printDetail();

    void reviewRequest();
    
    void assignJob();
    
    void reviewJob();

    static void writeToFile(const Manager& manage);

    static int getUniqueID();

    int getID() const;

    string getName() const;

    static void markAsUnallocated(int manageId);
};

#endif //_MANAGER_H