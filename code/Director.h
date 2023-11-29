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
    vector<Department>* depts;

public: 

    Director(vector<Department>& depts);

    int getID() const;

    string getName() const;
    
    void control();

    void complains_in_Dept();
    
    void complainsSummary();
    
    void complainDetail();
};

#endif //_DIRECTOR_H