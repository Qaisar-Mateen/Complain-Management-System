#include<iostream>
#include "Admin.h"

using namespace std;

int main()
{
	Admin* ad = new Admin();

	ad->addEmploye();

	ad->addTeacher();

	ad->addEmploye();

	ad->addManager();

	ad->addManager();

	ad->addEmploye();

	ad->addTeacher();

	ad->displayEmployes();

	ad->displayManagers();

	ad->displayTeachers();

	return 0;
}