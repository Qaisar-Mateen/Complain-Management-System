#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#define NOMINMAX
#include <windows.h>

// Forward declarations
class Person;
class Admin;
class Department;
class Employee;
class Manager;
class Teacher;
class Complaint;
class Director;
class Job;

using namespace std;

extern Director* dir;
extern Admin* adm;
extern vector<Employee*> emp;
extern vector<Manager*> man;
extern vector<Teacher*> tea;
extern vector<Department*> depts;
extern vector<Complaint*> coms;
extern vector<Job*> jobs;

void populateDepartment(string);
void populateComplaint(string);
void populateJob(string);
void populateEmployee(string);
void init(string, string, string, string, string, string);


template<typename t>
t* search(vector<t*>& per, int id)
{
	for (int i = 0; i < per.size(); i++)
	{
		if (per[i]->getID() == id)
			return per[i];
	}
	return nullptr;
}

template<typename T>
void populateFromFile(const string& fileName, vector<T*>& targetVector)
{
	ifstream file(fileName);
	if (file.is_open()) {
		int id;
		string name;

		while (file >> id) {
			// Read the entire line as the name, including spaces
			getline(file >> ws, name);
			// Construct the item using the entire name
			T* item = new T(id, name);
			targetVector.push_back(item);
		}

		file.close();
	}
	else {
		cout << "Unable to open the file " << fileName << endl;
	}
}