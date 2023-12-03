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
//    bool not_M;
    //bool not_T;
public:    
    Complaint(int ID, string des, int d, int t, int st, int day, int month, int year);
    Complaint(string des, int d, int t);

    int getID();

    State getState();

    void setState(State s);

    void displayState();
    
    void printDetail();

    void printFullDetail();

    int getUniqueID();

    void writeToFile(int, int);
};

#endif //_COMPLAINT_H