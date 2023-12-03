#include "Job.h"
#include "Date.h"
#include "Manager.h"
#include "Employee.h"
#include "Complaint.h"
#include "Global.h"

Job::Job(int c_id, Manager* m, vector<int> e) : com_id(c_id), man(m) {
	id = getUniqueID();
	for (int i = 0; i < e.size(); i++) {
		emps.push_back(search(emp, e[i]));
		emps.back()->addJob(this);
	}
	date = new Date();
	jobs.push_back(this); //add to global;
	Man_high = completed = false;
	writeToFile();
}

Job::Job(int iD, int c_id, Manager* m, vector<int> e, int day, int month, int year, int com, int hi): com_id(c_id), man(m) {
	id = iD;
	for (int i = 0; i < e.size(); i++) {
		emps.push_back(search(emp, e[i]));
		emps.back()->addJob(this);
	}
	date = new Date(day, month, year);
	man->addJob(this);
	completed = (bool)com;
	Man_high = (bool)hi;
}

void Job::read() { Man_high = false; }

int Job::getID() { return id; }

int Job::getComID() { return com_id; }

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

bool Job::isCompleted() { return completed; }

bool Job::isHighlight() { return Man_high; }

void Job::Complete(bool t) { completed = Man_high = t; }

void Job::printDetail(){
	cout << "\n ID: " << id << "\t Complaint Id: " << com_id << "\t Assigned to: ";
	for (auto it : emps)
		cout << it->getName() << ", ";
	cout << "\t Completed: "<< completed <<"\n";
}

void Job::writeToFile() {
	ofstream file("Job.txt", ios::app);
	if (file.is_open()) {
		file << id << ',' << com_id << ',' << man->getID() << ',';
		for (int i = 0; i < emps.size(); i++) {
			if(i == emps.size()-1)
				file << emps[i]->getID() << ',';
			else
				file << emps[i]->getID() << ' ';
		}
		file << date->getDay() << ',' << date->getMonth() << ',' << date->getYear() << ',' << (int)completed << ',' << (int)Man_high << endl;
		file.close();
	}
}