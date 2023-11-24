#include<iostream>
#include<windows.h>
#include<vector>

#include "Admin.h"
#include "Manager.h"
#include "Employee.h"
#include "Teacher.h"
#include "Director.h"

using namespace std;

Person* Login();
Manager* search(vector<Manager> &per, int id);
Teacher* search(vector<Teacher> &per, int id);
Employee* search(vector<Employee> &per, int id);

Director* dir;
Admin* adm;
vector<Employee> emp;
vector<Manager> man;
vector<Teacher> tea;

int main()
{
	////--------------------------------------------------------------
	adm = new Admin(emp, man, tea);
	////--------------------------------------------------------------
	//step1: populate all the classes from files with objects in main
	adm = new Admin();

	//step2: login into the system

	while (1) {
		Person* user = Login();
		if (user == nullptr)
			break;
		user->control();
	}

	//adm->addEmployee();
	adm->removeEmployee();
	adm->removeEmployee();
	cin.ignore();

	adm->addTeacher();

	adm->removeTeacher();

	adm->addManager();

	adm->addManager();
	adm->removeManager();
	cin.ignore();
	
	/*adm->displayEmployees();

	adm->displayManagers();

	adm->displayTeachers();*/

	return 0;
}

Person* Login()
{
	char opt;
	bool valid = false;
	Person* p = nullptr;
	
	while (!valid)
	{
		cout << "\t\t\t\t ---<><><><><><><><><><( Login )><><><><><><><><><>---\n\n";
		cout << "\n Login as: (choose one from below)\n";
		if(adm)
			cout << " a: Admin\n";
		if(dir)
			cout << " b: Director\n";
		if(!man.empty())
			cout << " c: Manager\n";
		if(!tea.empty())
			cout << " d: Teacher\n";
		if(!emp.empty())
			cout << " e: Employee\n";
		cout << " q: Quit\n";
		cout << " >";
		cin >> opt;
		int id, f = 0;

		if (opt == 'q')
		{
			cout << "\n Closing Complain Management System!!\n";
			valid = true;
		}

		else if (opt == 'a' && adm) 
		{
			cout << "\t\t\t\t ---<><><><><><><><><><( Admin )><><><><><><><><><>---\n\n\n";
			cout << " Enter Admin's ID: ";
			cin >> id;
			while (adm->getID() != id)
			{
				cout << "\n Invalid ID!!\n Enter Admin's ID: ";
				cin >> id;
			}
			cout << "\n You are now logged in as Admin \n";
			p = adm;
			valid = true;
		}

		else if (opt == 'b' && dir)
		{
			cout << "\t\t\t\t ---<><><><><><><><><><( Director )><><><><><><><><><>---\n\n\n";
			cout << " Enter Director's ID: ";
			cin >> id;
			while (dir->getID() != id)
			{
				cout << "\n Invalid ID!!\n Enter Director's ID: ";
				cin >> id;
			}
			cout << "\n You are now logged in as Director\n";
			p = dir;
			valid = true;
		}

		else if (opt == 'c' && !man.empty())
		{
			cout << "\t\t\t\t ---<><><><><><><><><><( Manager )><><><><><><><><><>---\n\n\n";
			cout << " Enter Manager's ID: ";
			do {
				cin >> id;
				p = search(man, id);
				if (p != nullptr)
					f = 1;
				if (f == 0)
					cout << "\n Invalid ID!!\n Enter Manager's ID: ";
			} while (f == 0);

			cout << "\n You are now logged in as Manager\n";

			valid = true;
		}

		else if (opt == 'd' && !tea.empty())
		{
			cout << "\t\t\t\t ---<><><><><><><><><><( Teacher )><><><><><><><><><>---\n\n\n";
			cout << " Enter Teacher's ID: ";
			do {
				cin >> id;
				p = search(tea, id);
				if (p != nullptr)
					f = 1;
				if (f == 0)
					cout << "\n Invalid ID!!\n Enter Teacher's ID: ";

			} while (f == 0);

			cout << "\n You are now logged in as Teacher\n";

			valid = true;
		}

		else if (opt == 'e' && !emp.empty())
		{
			cout << "\t\t\t\t ---<><><><><><><><><><( Employee )><><><><><><><><><>---\n\n\n";
			cout << " Enter Employee's ID: ";
			do {
				cin >> id;
				p = search(emp, id);
				if (p != nullptr)
					f = 1;
				if (f == 0)
					cout << "\n Invalid ID!!\n Enter Employee's ID: ";

			} while (f == 0);

			cout << "\n You are now logged in as Employee\n";
			valid = true;
		}

		else
		{
			cout << "\n Invalid!!\n";
			system("cls");
		}
		Sleep(700);
	}

	return p;
}

Manager* search(vector<Manager> &per, int id)
{	
	for (int i = 0; i < per.size(); i++)
	{
		if (per[i].getID() == id)
			return &per[i];		
	}

	return nullptr;
}

Teacher* search(vector<Teacher> &per, int id)
{
	for (int i = 0; i < per.size(); i++)
	{
		if (per[i].getID() == id)
			return &per[i];
	}

	return nullptr;
}

Employee* search(vector<Employee> &per, int id)
{
	for (int i = 0; i < per.size(); i++)
	{
		if (per[i].getID() == id)
			return &per[i];
	}

	return nullptr;
}