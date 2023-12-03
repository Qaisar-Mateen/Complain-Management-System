#include "Job.h"
#include "Date.h"
#include "Manager.h"
#include "Employee.h"
#include "Global.h"

Job::Job(int c_id, Manager* m, vector<int> e) : com_id(c_id), man(m) {
	id = getUniqueID();
	for (int i = 0; i < e.size(); i++) {
		emps.push_back(search(emp, e[i]));
		emps.back()->addJob(this);
	}
	date = new Date();
	jobs.push_back(this); //add to global;
}

Job::Job(int iD, int c_id, Manager* m, vector<int> e, int day, int month, int year): com_id(c_id), man(m) {
	id = iD;
	for (int i = 0; i < e.size(); i++) {
		emps.push_back(search(emp, e[i]));
		emps.back()->addJob(this);
	}
	date = new Date(day, month, year);
	man->addJob(this);
}

int Job::getUniqueID()
{
	ifstream file("Job.txt");
	int maxID = 1;
	int currentID;
	while (file >> currentID) {
		file.ignore();
		file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
		if (currentID == maxID) {
			maxID++;
		}
	}
	file.close();
	return maxID;
}
