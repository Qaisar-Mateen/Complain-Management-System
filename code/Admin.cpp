#include "Admin.h"

Admin::Admin()
{
	id = 0;
}

Admin::Admin(vector<Employe> e, vector<Manager> m, vector<Teacher> t)
{
	id = 0;
	Emps = e;
	Managers = m;
	Teachs = t;
}

void Admin::displayEmployes()
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

void Admin::addEmploye() 
{
	int i;
	string nam;

	cout << "\n Enter Employe Id: ";
	cin >> i;

	cout << "\n Enter Employe Name: ";
	cin >> nam;

	Employe* e = new Employe(i, nam);

	Emps.push_back(*e);
}

void Admin::addManager() {

	int i;
	string nam;

	cout << "\n Enter Manager Id: ";
	cin >> i;

	cout << "\n Enter Manager Name: ";
	cin >> nam;

	Manager* m = new Manager(i, nam);

	Managers.push_back(*m);
}

void Admin::addTeacher() {

	int i;
	string nam;

	cout << "\n Enter Teacher Id: ";
	cin >> i;

	cout << "\n Enter Teacher Name: ";
	cin >> nam;

	Teacher* t = new Teacher(i, nam);

	Teachs.push_back(*t);
}

void Admin::removeEmploye() {

}

void Admin::removeTeacher() {

}

void Admin::removeManager() {

}