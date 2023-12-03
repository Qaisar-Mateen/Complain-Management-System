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
	bool completed;
	bool Man_high;

public:
	Job(int c_id, Manager* m, vector<int> e);

	Job(int iD, int c_id, Manager* m, vector<int> e, int day, int month, int year, int com, int hi);

	void read();

	int getID();

	int getComID();

	int getUniqueID();

	bool isCompleted();

	bool isHighlight();

	void Complete(bool t);

	void printDetail();

	void writeToFile();
};

#endif //_JOB_H