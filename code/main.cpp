#include<iostream>
#include "Admin.h"

using namespace std;

int main()
{
	Admin* ad = new Admin();

	ad->addEmploye();

	ad->addEmploye();
	
	ad->removeEmploye();

	ad->addTeacher();

	ad->addTeacher();

	ad->removeTeacher();

	/*ad->addManager();

	ad->addManager();

	ad->removeManager();*/

	/*ad->displayEmployes();

	ad->displayManagers();

	ad->displayTeachers();*/

	return 0;
}