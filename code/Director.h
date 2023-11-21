#include<string>
#include"Person.h"

using namespace std;

#ifndef _DIRECTOR_H
#define _DIRECTOR_H

class Director: virtual public Person {
    int id;
    string Name;

public: 


    int getID() const;

    string getName() const;
    
    void control();

    void complains_in_Dept();
    
    void complainsSummary();
    
    void complainDetail();
};

#endif //_DIRECTOR_H