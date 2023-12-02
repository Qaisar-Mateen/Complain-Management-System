#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Person.h"
using namespace std;

class Complaint;

#ifndef _TEACHER_H
#define _TEACHER_H

class Teacher : virtual public Person {
    int id;
    string name;
    vector<Complaint*> comps;

public:

    Teacher();

    Teacher(int, string);

    void control();

    char printInterface();

    void complaintDetail();

    void printDetail();

    void makeComplaint();
        
    void reocordFeedback();

    static void writeToFile(const Teacher& teach);

    static int getUniqueID();

    int getID() const;

    string getName() const;

    void addComplaint(Complaint* c);

    static void markAsUnallocated(int teachId);
};

#endif //_TEACHER_H