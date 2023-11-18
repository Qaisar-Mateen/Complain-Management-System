#include <iostream>
#include <string>

using namespace std;

#ifndef _TEACHER_H
#define _TEACHER_H

class Teacher {
    int id;
    string name;

public:

    Teacher();

    Teacher(int, string);

    void printDetail();

    void makeComplain();
    
    void printComplains();
        
    void reocordFeedback();
};

#endif //_TEACHER_H