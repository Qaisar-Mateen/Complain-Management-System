#pragma once
#include "Admin.h"
#include "Employee.h"
#include "Manager.h"
#include "Department.h"
#include "Teacher.h"
#include "Global.h"

Admin::Admin()
{
	id = 0;
	Name = "admin";
}

Admin::Admin(vector<Employee*> &e, vector<Manager*> &m, vector<Teacher*> &t)
{
	id = 0;
	Name = "admin";
	Emps = &e;
	Managers = &m;
	Teachs = &t;
}

int Admin::getID() const
{
	return id;
}

string Admin::getName() const
{
	return Name;
}

char Admin::printInterface()
{
	bool valid = false;
	char opt;
	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		cout << "\n --<{ Admin Controls }>--\n";
		cout << " a: Add Someone\n";
		if(!Managers->empty() || !Teachs->empty() || !Emps->empty())
			cout << " b: Remove Someone\n";
		cout << " c: Print Detail\n";
		cout << " f: Log out\n";
		cout << " >";
		cin >> opt;

		if (opt == 'a' || opt == 'c' || opt == 'f')
			valid = true;
		else if (opt == 'b' && (!Managers->empty() || !Teachs->empty() || !Emps->empty()))
			valid = true;
		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}

char Admin::printAddInterface()
{
	bool valid = false;
	char opt;
	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		cout << "\n --<{ Admin Controls }>--\n";
		cout << " a: Add Employee\n";
		cout << " b: Add Manager\n";
		cout << " c: Add Teacher\n";
		cout << " l: Go Back\n";
		cout << " >";
		cin >> opt;

		if (opt == 'a' || opt == 'c' || opt == 'b' || opt == 'l')
			valid = true;

		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}

char Admin::printRemoveInterface()
{
	bool valid = false;
	char opt;
	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		cout << "\n --<{ Admin Controls }>--\n";
		if(!Emps->empty())
			cout << " a: Remove Employee\n";
		if (!Managers->empty())
			cout << " b: Remove Manager\n";
		if (!Teachs->empty())
			cout << " c: Remove Teacher\n";
		cout << " l: Go Back\n";
		cout << " >";
		cin >> opt;

		if (opt == 'l')
			valid = true;
		else if (opt == 'a' && !Emps->empty())
			valid = true;
		else if (opt == 'b' && !Managers->empty())
			valid = true;
		else if (opt == 'c' && !Teachs->empty())
			valid = true;
		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}

char Admin::printDetailInterface()
{
	bool valid = false;
	char opt;

	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		cout << "\n --<{ Admin Controls }>--\n";
		cout << " a: Print Detail of Employees\n";
		cout << " b: Print Detail of Managers\n";
		cout << " c: Print Detail of Teachers\n";
		cout << " l: Go Back\n";
		cout << " >";
		cin >> opt;

		if (opt == 'a' || opt == 'b' || opt == 'c' || opt == 'l')
			valid = true;

		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}

void Admin::control()
{
	char opt = 'd';

	while (opt != 'f')
	{
		opt = printInterface();

		if (opt == 'a')
		{
			opt = printAddInterface();
			if (opt == 'a')
				addEmployee();	
			else if (opt == 'b')
				addManager();
			else if (opt == 'c')
				addTeacher();
		}

		else if (opt == 'b')
		{
			opt = printRemoveInterface();
			if (opt == 'a')
				removeEmployee();
			else if (opt == 'b')
				removeManager();
			else if (opt == 'c')
				removeTeacher();
		}

		else if (opt == 'c')
		{
			opt = printDetailInterface();
			if (opt == 'a')
				displayEmployees();
			else if (opt == 'b')
				displayManagers();
			else if (opt == 'c')
				displayTeachers();
		}
		if(opt != 'f' && opt != 'l')
		{ 
			cin.ignore();
			cout << "\n Press any key to continue...";
			cin.get();
		}
	}
	cout << "\n Logging out...";
	Sleep(700);
	system("cls");
}

void Admin::displayEmployees()
{
	if (Emps->empty())
	{
		cout << "\n No Employee to Display\n";
		return ;
	}
	cout << "\n\t\t\t--<{ All Employees Detail}>--\n";

	for (int i = 0; i < Emps->size(); i++)
		(*Emps)[i]->printDetail();
}

void Admin::displayManagers()
{
	if (Managers->empty())
	{
		cout << "\n No Manager to Display\n";
		return;
	}
	cout << "\n\t\t\t--<{ All Managers Detail }>--\n";

	for (int i = 0; i < Managers->size(); i++)
		(*Managers)[i]->printDetail();
}

void Admin::displayTeachers()
{
	if (Teachs->empty())
	{
		cout << "\n No Teacher to Display\n";
		return;
	}
	cout << "\n\t\t\t--<{ All Teachers Detail }>--\n";

	for (int i = 0; i < Teachs->size(); i++)
		(*Teachs)[i]->printDetail();
}

void Admin::addEmployee()
{
	string nam;

	// Automatically generate a unique ID
	int id = Employee::getUniqueID(), d_id;
	cin.ignore();
	cout << "\n Enter Employee Name: ";
	getline(cin, nam);
	cout << "\n Enter Employee department id: ";
	cin >> d_id;

	Department* d =  search(depts, d_id);

	if (!d) {
		cerr << "\n Invalid Department Id!!\n";
		return;
	}
	Employee* e = new Employee(id, nam);

	e->addDept(d);
	Emps->push_back(e);
	d->addEmployee(e);

	Employee::writeToFile(*e);

	cout << "\n Employee added successfully.\n";
	e->printDetail();
}

void Admin::addManager() {

	string nam;

	// Automatically generate a unique ID
	int id = Manager::getUniqueID(), d_id;

	cin.ignore();
	cout << "\n Enter Manager Name: ";
	getline(cin, nam);
	cin.ignore();

	cout << "\n Enter Manager department id: ";
	cin >> d_id;

	Manager* mg = new Manager(id, nam);

	Managers->push_back(mg);

	// Write manager data to the file
	Manager::writeToFile(*mg);

	// Display details
	cout << "\n Manager added successfully.\n";
	mg->printDetail();
}

void Admin::addTeacher() {
	string nam;

	// Automatically generate a unique ID
	int id = Teacher::getUniqueID();

	cin.ignore();
	cout << "\n Enter Teacher Name: ";
	getline(cin, nam);
	cin.ignore();

	Teacher* t = new Teacher(id, nam);

	Teachs->push_back(t);

	// Write teacher data to the file
	Teacher::writeToFile(*t);

	// Display details
	cout << "\n Teacher added successfully.\n";
	t->printDetail();
}

void Admin::removeEmployee() {
	int empId;
	cin.ignore();
	cout << "\n Enter Employee ID to remove: ";
	cin >> empId;
	if(emp_delete(empId))
		Employee::markAsUnallocated(empId);
	else
		cerr << "\n Error: Failed to Remove, invalid ID!!\n";
}

void Admin::removeTeacher() {
	int tId;
	cin.ignore();
	cout << "\n Enter Teacher ID to remove: ";
	cin >> tId;
	if (tea_delete(tId))
		Teacher::markAsUnallocated(tId);
	else
		cerr << "\n Error: Failed to Remove, invalid ID!!\n";
}

void Admin::removeManager() {
	int mId;
	cin.ignore();
	cout << "\n Enter Manager ID to remove: ";
	cin >> mId;
	if (man_delete(mId))
		Manager::markAsUnallocated(mId);
	else
		cerr << "\n Error: Failed to Remove, invalid ID!!\n";
}

bool Admin::emp_delete(int Id)
{
	for (auto it = Emps->begin(); it != Emps->end(); ++it)
	{
		if ((*it)->getID() == Id)
		{
			it = Emps->erase(it);
			return true;
		}
	}
	return false;
}

bool Admin::man_delete(int Id)
{
	for (auto it = Managers->begin(); it != Managers->end(); ++it)
	{
		if ((*it)->getID() == Id)
		{
			it = Managers->erase(it);
			return true;
		}
	}
	return false;
}

bool Admin::tea_delete(int Id)
{
	for (auto it = Teachs->begin(); it != Teachs->end(); ++it)
    {
        if ((*it)->getID() == Id)
        {
            it = Teachs->erase(it);
            return true;
        }
    }
    return false;
}