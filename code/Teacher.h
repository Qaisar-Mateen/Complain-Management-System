#include <iostream>
#include <string>
#include <fstream>

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

    static void writeToFile(const Teacher& teach);

    static int getUniqueID();

    int getID() const;

    string getName() const;

    static void markAsUnallocated(int teachId);
};

#endif //_TEACHER_H