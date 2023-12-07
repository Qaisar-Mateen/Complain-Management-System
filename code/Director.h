#include<string>
#include"Person.h"
#include "Department.h"

using namespace std;

#ifndef _DIRECTOR_H
#define _DIRECTOR_H

class Department;

class Director: virtual public Person {
    int id;
    string Name;
    vector<Reports*> depts;

public: 
    Director(vector<Department*>& depts);

    int getID() const;

    void control();
private:
    string getName() const;
    char printInterface();
    void complains_in_Dept();
    void viewComplaintSummary();
};

#endif //_DIRECTOR_H