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

Director* dir;
Admin* adm;
vector<Employee> emp;
vector<Manager> man;
vector<Teacher> tea;

int main()
{

	//step1: populate all the classes from files with objects in main
	adm = new Admin();

	//step2: login into the system

	Person* user = Login();

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
		cout << " a: Admin\n";
		cout << " b: Director\n";
		cout << " c: Manager\n";
		cout << " d: Teacher\n";
		cout << " e: Employee\n >";
		cin >> opt;
		int id, f = 0;
		switch (opt)
		{
		case 'a':
			cout << "\t\t\t\t ---<><><><><><><><><><( Admin )><><><><><><><><><>---\n\n\n";
			cout << "Enter Admin's ID: ";
			cin >> id;
			while (adm->getID() != id)
			{
				cout << "\n Invalid ID\n Enter Admin's ID: ";
				cin >> id;
			}
			cout << "\n You are now logged in as Admin \n";
			p = adm;
			valid = true;
			break;

		case 'b':
			cout << "\t\t\t\t ---<><><><><><><><><><( Director )><><><><><><><><><>---\n\n\n";
			cout << "Enter Director's ID: ";
			cin >> id;
			while (dir->getID() != id)
			{
				cout << "\n Invalid ID!!\n Enter Director's ID: ";
				cin >> id;
			}
			cout << "\n You are now logged in as Director\n";
			p = dir;
			valid = true;
			break;

		case 'c':
			cout << "\t\t\t\t ---<><><><><><><><><><( Manager )><><><><><><><><><>---\n\n\n";
			cout << "Enter Manager's ID: ";
			do{
				cin >> id;
				for (int i = 0; i < man.size(); i++)
				{
					Manager* m = &man[i];
					if (m->getID() == id) {
						f = 1;
						p = m;
						break;
					}
				}

				if(f == 0)
					cout << "\n Invalid ID!!\n Enter Manager's ID: ";

			} while (f == 0);

			cout << "\n You are now logged in as Manager\n";
			
			valid = true;
			break;

		case 'd':
			cout << "\t\t\t\t ---<><><><><><><><><><( Teacher )><><><><><><><><><>---\n\n\n";
			cout << "Enter Teacher's ID: ";
			do {
				cin >> id;
				for (int i = 0; i < tea.size(); i++)
				{
					Teacher* m = &tea[i];
					if (m->getID() == id) {
						f = 1;
						p = m;
						break;
					}
				}

				if (f == 0)
					cout << "\n Invalid ID!!\n Enter Teacher's ID: ";

			} while (f == 0);

			cout << "\n You are now logged in as Teacher\n";

			valid = true;
			break;

		case 'e':
			cout << "\t\t\t\t ---<><><><><><><><><><( Employee )><><><><><><><><><>---\n\n\n";
			cout << "Enter Employee's ID: ";
			do {
				cin >> id;
				for (int i = 0; i < emp.size(); i++)
				{
					Employee* m = &emp[i];

					if (m->getID() == id) {
						f = 1;
						p = m;
						break;
					}
				}

				if (f == 0)
					cout << "\n Invalid ID!!\n Enter Employee's ID: ";

			} while (f == 0);

			cout << "\n You are now logged in as Employee\n";

			valid = true;
			break;

		default:
			cout << "\n Invalid!!\n";
			Sleep(1000);
			system("cls");
			break;
		}

	}

	return p;
}

Person* Search(int id, vector<Person*> user)
{

	for (Person* person : user) {
		if (person->getID() == id) {
			return person;
		}
	}


	return nullptr; //id does not exist
}