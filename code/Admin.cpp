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

//overrided constructor for administrator
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

// to print and handle the main interface of admin
// Function to print the Admin's main interface and get the user's option
char Admin::printInterface()
{
	bool valid = false;
	char opt;
	do {
		// Clear the console
		system("cls");
		// Print the Admin's details
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		// Print the available options
		cout << "\n --<{ Admin Controls }>--\n";
		cout << " a: Add Someone\n";
		// Only show the "Remove Someone" option if there are Managers, Teachers, or Employees
		if (!Managers->empty() || !Teachs->empty() || !Emps->empty())
			cout << " b: Remove Someone\n";
		cout << " c: Print Detail\n";
		cout << " f: Log out\n";
		cout << " >";
		// Get the user's option
		cin >> opt;

		// Validate the user's option
		if (opt == 'a' || opt == 'c' || opt == 'f')
			valid = true;
		else if (opt == 'b' && (!Managers->empty() || !Teachs->empty() || !Emps->empty()))
			valid = true;
		else {
			// Print an error message if the user's option is invalid
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	// Return the user's option
	return opt;
}

// Function to print the Admin's "Add" interface and get the user's option
char Admin::printAddInterface()
{
	bool valid = false;
	char opt;
	do {
		// Clear the console
		system("cls");
		// Print the Admin's details
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		// Print the available options
		cout << "\n --<{ Admin Controls }>--\n";
		cout << " a: Add Employee\n";
		cout << " b: Add Manager\n";
		cout << " c: Add Teacher\n";
		cout << " l: Go Back\n";
		cout << " >";
		// Get the user's option
		cin >> opt;

		// Validate the user's option
		if (opt == 'a' || opt == 'c' || opt == 'b' || opt == 'l')
			valid = true;
		else {
			// Print an error message if the user's option is invalid
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	// Return the user's option
	return opt;
}

// Function to print the Admin's "Remove" interface and get the user's option
char Admin::printRemoveInterface()
{
	bool valid = false;
	char opt;
	do {
		// Clear the console
		system("cls");
		// Print the Admin's details
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		// Print the available options
		cout << "\n --<{ Admin Controls }>--\n";
		// Only show the "Remove Employee" option if there are Employees
		if (!Emps->empty())
			cout << " a: Remove Employee\n";
		// Only show the "Remove Manager" option if there are Managers
		if (!Managers->empty())
			cout << " b: Remove Manager\n";
		// Only show the "Remove Teacher" option if there are Teachers
		if (!Teachs->empty())
			cout << " c: Remove Teacher\n";
		cout << " l: Go Back\n";
		cout << " >";
		// Get the user's option
		cin >> opt;

		// Validate the user's option
		if (opt == 'l')
			valid = true;
		else if (opt == 'a' && !Emps->empty())
			valid = true;
		else if (opt == 'b' && !Managers->empty())
			valid = true;
		else if (opt == 'c' && !Teachs->empty())
			valid = true;
		else {
			// Print an error message if the user's option is invalid
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	// Return the user's option
	return opt;
}

// Function to print the Admin's "Detail" interface and get the user's option
char Admin::printDetailInterface()
{
	bool valid = false;
	char opt;

	do {
		// Clear the console
		system("cls");
		// Print the Admin's details
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		// Print the available options
		cout << "\n --<{ Admin Controls }>--\n";
		cout << " a: Print Detail of Employees\n";
		cout << " b: Print Detail of Managers\n";
		cout << " c: Print Detail of Teachers\n";
		cout << " l: Go Back\n";
		cout << " >";
		// Get the user's option
		cin >> opt;

		// Validate the user's option
		if (opt == 'a' || opt == 'b' || opt == 'c' || opt == 'l')
			valid = true;
		else {
			// Print an error message if the user's option is invalid
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	// Return the user's option
	return opt;
}

// Function that controls the Admin module
void Admin::control()
{
	char opt = 'd';

	// Keep running until the user chooses to log out
	while (opt != 'f')
	{
		// Print the main interface and get the user's option
		opt = printInterface();

		// If the user chooses to add someone
		if (opt == 'a')
		{
			// Print the "Add" interface and get the user's option
			opt = printAddInterface();
			// Add an Employee, Manager, or Teacher based on the user's option
			if (opt == 'a')
				addEmployee();
			else if (opt == 'b')
				addManager();
			else if (opt == 'c')
				addTeacher();
		}

		// If the user chooses to remove someone
		else if (opt == 'b')
		{
			// Print the "Remove" interface and get the user's option
			opt = printRemoveInterface();
			// Remove an Employee, Manager, or Teacher based on the user's option
			if (opt == 'a')
				removeEmployee();
			else if (opt == 'b')
				removeManager();
			else if (opt == 'c')
				removeTeacher();
		}

		// If the user chooses to print details
		else if (opt == 'c')
		{
			// Print the "Detail" interface and get the user's option
			opt = printDetailInterface();
			// Display the details of Employees, Managers, or Teachers based on the user's option
			if (opt == 'a')
				displayEmployees();
			else if (opt == 'b')
				displayManagers();
			else if (opt == 'c')
				displayTeachers();
		}
		// If the user doesn't choose to log out or go back, wait for the user to press a key before continuing
		if (opt != 'f' && opt != 'l')
		{
			cin.ignore();
			cout << "\n Press any key to continue...";
			cin.get();
		}
	}
	// Log out
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
	Employee* e = new Employee(id, nam, true);

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

	cout << "\n Note: Manager of this department will be deleted first!!\n";		

	cout << "\n Enter Manager department id: ";									
	cin >> d_id;

	Department* d = search(depts, d_id);

	if (!d) {
		cerr << "\n Invalid Department Id!!\n";
		return;
	}

	Manager* mg = new Manager(id, nam);

	Managers->push_back(mg);

	d->changeManager(mg);

	// Write manager data to the file
	Manager::writeToFile(*mg);

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

	Teacher* t = new Teacher(id, nam);

	Teachs->push_back(t);

	// Write teacher data to the file
	Teacher::writeToFile(*t);

	// Display details
	cout << "\n Teacher added successfully.\n";
	t->printDetail();
}

void Admin::removeEmployee() { //removing employee
	int empId;
	cin.ignore();
	cout << "\n Enter Employee ID to remove: ";
	cin >> empId;
	int flag = emp_delete(empId);
	if(flag == 1)
		Employee::markAsUnallocated(empId);
	else if(flag == 0)
		cerr << "\n Error: Failed to Remove, invalid ID!!\n";
}

void Admin::removeTeacher() {  //to remove teacher

	int tId;
	cin.ignore();
	cout << "\n Enter Teacher ID to remove: ";
	cin >> tId;
	if (tea_delete(tId))
		Teacher::markAsUnallocated(tId);
	else
		cerr << "\n Error: Failed to Remove, invalid ID!!\n";
}

void Admin::removeManager() { //for removing manager
	int mId;
	cin.ignore();
	cout << "\n Enter Manager ID to remove: ";
	cin >> mId;
	if (man_delete(mId))
		Manager::markAsUnallocated(mId);
	else
		cerr << "\n Error: Failed to Remove, invalid ID!!\n";
}

int Admin::emp_delete(int Id) //helper for deleting employee
{
	for (auto it = Emps->begin(); it != Emps->end(); ++it)
	{
		if ((*it)->getID() == Id)
		{
			if (!(*it)->isAvailable()) {
				cout << "\n Can't Remove Employee: Currently Assigned a Job\n";
				return -1;
			}
			delete *it; // Delete the Employee object
			it = Emps->erase(it);
			return 1;
		}
	}
	return 0;
}

bool Admin::man_delete(int Id) //helper for deleting manager
{
	for (auto it = Managers->begin(); it != Managers->end(); ++it)
	{
		if ((*it)->getID() == Id)
		{
			cout << "\n Note: Add data for new Manager!!\n";
			string nam;
			int id = Manager::getUniqueID(), d_id;
			cin.ignore();									//adding new manager
			cout << "\n Enter Manager Name: ";				//to preserve manager condition
			getline(cin, nam);

			d_id = (*it)->getDeptId();
			Department* d = search(depts, d_id);
			Manager* mg = new Manager(id, nam);

			Managers->push_back(mg);
			d->changeManager(mg);

			Manager::writeToFile(*mg);
			mg->printDetail();
			return true;
		}
	}
	return false;
}

bool Admin::tea_delete(int Id)	//helper for deleting teacher
{
	for (auto it = Teachs->begin(); it != Teachs->end(); ++it)
    {
        if ((*it)->getID() == Id)
        {
			delete *it; // Delete the Teacher object
            it = Teachs->erase(it);
            return true;
        }
    }
    return false;
}