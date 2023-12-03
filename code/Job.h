#include<string>
#include <vector>

using namespace std;

#ifndef _JOB_H
#define _JOB_H

class Date;
class Manager;
class Employee;

class Job {
	int id;
	int com_id;
	Date* date;
	Manager* man;
	vector<Employee*> emps;

public:
	Job(int c_id, Manager* m, vector<int> e);

	Job(int iD, int c_id, Manager* m, vector<int> e, int day, int month, int year);

	int getUniqueID();
};

#endif //_JOB_H