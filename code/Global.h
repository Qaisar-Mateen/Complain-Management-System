#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include "Person.h"
#include "Admin.h"
#include "Department.h"
#include "Employee.h"
#include "Manager.h"
#include "Teacher.h"
#include "Complaint.h"
#include "Director.h"

using namespace std;

Director* dir;
Admin* adm;
vector<Employee> emp;
vector<Manager> man;
vector<Teacher> tea;
vector<Department> dept;

template<typename T>
void populateFromFile(const string&, vector<T>& );
template<typename t>
t* search(vector<t>& , int );
void init(string, string, string, string);
void populateDepartment(string);


template<typename t>
t* search(vector<t>& per, int id)
{
	for (int i = 0; i < per.size(); i++)
	{
		if (per[i].getID() == id)
			return &per[i];
	}

	return nullptr;
}



template<typename T>
void populateFromFile(const string& fileName, vector<T>& targetVector) 
{
	ifstream file(fileName);
	if (file.is_open()) {
		int id;
		string name;

		while (file >> id) {
			// Read the entire line as the name, including spaces
			getline(file >> ws, name);
			// Construct the item using the entire name
			T item(id, name);
			targetVector.push_back(item);
		}

		file.close();
	}
	else {
		cout << "Unable to open the file " << fileName << endl;
	}
}

void populateDepartment(string filename)
{
	ifstream file(filename);

	if (!file.is_open()) {
		cerr << "Error opening file." << endl;
		return;
	}

	string line;
	while (getline(file, line))
	{
		istringstream iss(line);
		int man_id, dept_id;
		vector<int> emp_id, comp_id;
		string name;

		iss >> dept_id >> ws; // Skip whitespaces
		getline(iss, name, '\'');
		iss >> man_id >> ws;

		// Process the employee ids
		iss.ignore(); // Skip the opening quote
		int employee_id;
		while (iss >> employee_id >> ws)
			emp_id.push_back(employee_id);

		dept.push_back(Department(dept_id, name, search(man, man_id)));

		for (int i = 0; i < emp_id.size(); i++)
			dept.back().addEmployee(search(emp, emp_id[i]));
	}
	file.close();
}


void init(string e_file, string m_file, string t_file, string d_file)
{
	adm = new Admin(emp, man, tea);
	dir = new Director(dept);

	populateFromFile(e_file, emp);
	populateFromFile(m_file, man);
	populateFromFile(t_file, tea);

	populateDepartment(d_file);
}
