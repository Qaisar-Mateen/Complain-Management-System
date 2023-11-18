#include <string>
#include <iostream>
using namespace std;

#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H

class Employe {
    int id;
    string name;

public:
    Employe();

    Employe(int ID, string Name);

    void printDetail();

    void updateSystem();

    ~Employe();
};

#endif //_EMPLOYEE_H