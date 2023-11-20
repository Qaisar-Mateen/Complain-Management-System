#include<iostream>
#include "Admin.h"

using namespace std;

int main()
{



	Admin* ad = new Admin();

	ad->addEmployee();

	ad->addEmployee();

	ad->removeEmployee();

	ad->addTeacher();

	ad->addTeacher();

	ad->removeTeacher();

	ad->addManager();

	ad->addManager();

	ad->removeManager();

	/*ad->displayEmployees();

	ad->displayManagers();

	ad->displayTeachers();*/

	return 0;
}