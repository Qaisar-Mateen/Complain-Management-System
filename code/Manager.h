#include <string>
#include <iostream>
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
};

#endif //_MANAGER_H