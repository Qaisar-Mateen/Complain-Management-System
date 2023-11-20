#include "Admin.h"

Admin::Admin()
{
	id = 0;
	Name = "admin";
}

Admin::Admin(vector<Employee> e, vector<Manager> m, vector<Teacher> t)
{
	id = 0;
	Name = "admin";
	Emps = e;
	Managers = m;
	Teachs = t;
}

int Admin::getID() const
{
	return id;
}

string Admin::getName() const
{
	return Name;
}

void Admin::displayEmployees()
{
	cout << "\n\t\t\t Employees\n";

	for (int i = 0; i < Emps.size(); i++)
		Emps[i].printDetail();

}

void Admin::displayManagers()
{
	cout << "\n\t\t\t Managers\n";

	for (int i = 0; i < Managers.size(); i++)
		Managers[i].printDetail();
}

void Admin::displayTeachers()
{
	cout << "\n\t\t\t Teachers\n";

	for (int i = 0; i < Teachs.size(); i++)
		Teachs[i].printDetail();
}

void Admin::addEmployee()
{
	string nam;

	// Automatically generate a unique ID
	int id = Employee::getUniqueID();

	cout << "\n Enter Employee Name: ";
	getline(cin, nam);

	Employee* e = new Employee(id, nam);

	Emps.push_back(*e);

	// Write employee data to the file
	Employee::writeToFile(*e);

	// Display details
	cout << "\n Employee added successfully.\n";
	e->printDetail();
}

void Admin::addManager() {

	string nam;

	// Automatically generate a unique ID
	int id = Manager::getUniqueID();

	cout << "\n Enter Manager Name: ";
	getline(cin, nam);

	Manager* mg = new Manager(id, nam);

	Managers.push_back(*mg);

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

	cout << "\n Enter Teacher Name: ";
	getline(cin, nam);

	Teacher* t = new Teacher(id, nam);

	Teachs.push_back(*t);

	// Write teacher data to the file
	Teacher::writeToFile(*t);

	// Display details
	cout << "\n Teacher added successfully.\n";
	t->printDetail();
}

void Admin::removeEmployee() {
	int empId;
	cout << "\n Enter Employee ID to remove: ";
	cin >> empId;
	Employee::markAsUnallocated(empId);
}

void Admin::removeTeacher() {
	int tId;
	cout << "\n Enter Teacher ID to remove: ";
	cin >> tId;
	Teacher::markAsUnallocated(tId);
}

void Admin::removeManager() {
	int mId;
	cout << "\n Enter Manager ID to remove: ";
	cin >> mId;
	Manager::markAsUnallocated(mId);
}