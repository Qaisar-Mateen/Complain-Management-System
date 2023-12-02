#pragma once
#include<string>
#include "Date.h"

using namespace std;

#ifndef _COMPLAINT_H
#define _COMPLAINT_H

enum class State { New, Assigned, Resolved, Closed };

class Department;
class Teacher;

class Complaint 
{
    int id;
    string description;
    Department* To;
    Teacher* From;
    Date* date;
    State state;

public:    
    Complaint(int ID, string des, Department* d, Teacher* teacher, int st, int day, int month, int year);
    Complaint(string des, int d_id, Teacher* teacher);

    void setState(State s);

    void displayState();

    void currState();
        
    void changeState();
    
    void printDetail();

    int getUniqueID();

    void writeToFile();
};

#endif //_COMPLAINT_H