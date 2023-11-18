/**
 * Project Complain Management System
 */

#include<string>

using namespace std;

#ifndef _COMPLAIN_H
#define _COMPLAIN_H

class Complain {
public: 
    int id;
    string description;
    
void currState();
    
void changeState();
    
void printDetail();
};

#endif //_COMPLAIN_H