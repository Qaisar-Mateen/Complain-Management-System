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
    bool notify_m;
    bool notify_t;
public:    
    Complaint(int ID, string des, int d, int t, int st, int day, int month, int year, int noT, int nom);
    Complaint(string des, int d, int t);

    int getID();

    State getState();

    void setState(State s);

    bool notifyManager();

    bool notifyTeacher();

    void setNotifyMan(bool t);

    void setNotifyTea(bool t);

    void displayState();
    
    void printDetail();

    void printFullDetail();

    int getUniqueID();

    void writeToFile(int, int);

    void updateFile(State newState, bool newNotifyTeacher, bool newNotifyManager);
};

#endif //_COMPLAINT_H