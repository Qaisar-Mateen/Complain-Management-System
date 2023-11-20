#include<iostream>
#include "Admin.h"

using namespace std;

int main()
{
	Admin* ad = new Admin();

	//ad->addEmployee();
	ad->removeEmployee();
	ad->removeEmployee();
	cin.ignore();

	ad->addTeacher();
	ad->removeTeacher();
	cin.ignore();

	ad->addManager();
	ad->removeManager();
	cin.ignore();
	
	/*ad->displayEmployees();

	ad->displayManagers();

	ad->displayTeachers();*/

	return 0;
}