#pragma once
#include<string>

using namespace std;

#ifndef _COMPLAINT_H
#define _COMPLAINT_H

class Department;
class Teacher;

class Complaint 
{
    int id;
    string description;
    Department* to;
    Teacher* From;


public:
    
void currState();
    
void changeState();
    
void printDetail();
};

#endif //_COMPLAINT_H