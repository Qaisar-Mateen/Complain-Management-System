#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

class Employe {
    int id;
    string name;

public:
    Employe();

    Employe(int ID, string Name);

    static void writeToFile(const Employe& emp);

    static int getUniqueID();

    int getID() const;

    string getName() const;

    void printDetail();

    void updateSystem();

    static void markAsUnallocated(int empId);

    ~Employe();
};

#endif //_EMPLOYEE_H