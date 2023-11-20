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
	string nam;

	// Automatically generate a unique ID
	int id = Employe::getUniqueID();

	cout << "\n Enter Employe Name: ";
	cin >> nam;

	Employe* e = new Employe(id, nam);

	Emps.push_back(*e);

	// Write employee data to the file
	Employe::writeToFile(*e);

	// Display details
	cout << "\n Employee added successfully.\n";
	e->printDetail();
}

void Admin::addManager() {

	string nam;

	// Automatically generate a unique ID
	int id = Manager::getUniqueID();

	cout << "\n Enter Manager Name: ";
	cin >> nam;

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
	cin >> nam;

	Teacher* t = new Teacher(id, nam);

	Teachs.push_back(*t);

	// Write teacher data to the file
	Teacher::writeToFile(*t);

	// Display details
	cout << "\n Teacher added successfully.\n";
	t->printDetail();
}

void Admin::removeEmploye() {
	int empId;
	cout << "\n Enter Employee ID to remove: ";
	cin >> empId;
	Employe::markAsUnallocated(empId);
	cout << "Employee with ID " << empId << " removed successfully.\n";
}

//void Admin::removeEmployeFromFile(int empId) {
//	ifstream inFile("employees.txt");
//	ofstream outFile("temp.txt");
//
//	int currentID;
//	string currentName;
//
//	while (inFile >> currentID >> currentName) {
//		if (currentID == empId) {
//			// Mark the employee as unallocated by writing '-' as the name
//			outFile << currentID << " -" << endl;
//		}
//		else {
//			outFile << currentID << " " << currentName << endl;
//		}
//	}
//
//	inFile.close();
//	outFile.close();
//
//	// Rename the temp file to replace the original file
//	remove("employees.txt");
//	rename("temp.txt", "employees.txt");
//}

void Admin::removeTeacher() {
	int tId;
	cout << "Enter Teacher ID to remove: ";
	cin >> tId;
	Teacher::markAsUnallocated(tId);
	cout << "Teacher with ID " << tId << " removed successfully.\n";
}

void Admin::removeManager() {
	int mId;
	cout << "Enter Manager ID to remove: ";
	cin >> mId;
	Manager::markAsUnallocated(mId);
	cout << "Manager with ID " << mId << " removed successfully.\n";
}