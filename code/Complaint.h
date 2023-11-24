#include<string>

using namespace std;

#ifndef _COMPLAINT_H
#define _COMPLAINT_H

class Complaint {
public: 
    int id;
    string description;
    
void currState();
    
void changeState();
    
void printDetail();
};

#endif //_COMPLAINT_H