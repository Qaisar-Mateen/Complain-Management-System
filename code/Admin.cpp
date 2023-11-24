#include "Admin.h"

Admin::Admin()
{
	id = 0;
	Name = "admin";
	populateFromFile("Employee.txt", Emps);
	populateFromFile("Manager.txt", Managers);
	populateFromFile("Teacher.txt", Teachs);
}

Admin::Admin(vector<Employee> e, vector<Manager> m, vector<Teacher> t)
{
	id = 0;
	Name = "admin";
	populateFromFile("Employee.txt", Emps);
	populateFromFile("Manager.txt", Managers);
	populateFromFile("Teacher.txt", Teachs);
	//Emps = e;
	//Managers = m;
	//Teachs = t;
}

int Admin::getID() const
{
	return id;
}

string Admin::getName() const
{
	return Name;
}

char Admin::printInterface()
{
	bool valid = false;
	char opt;
	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		cout << "\n --<{ Admin Controls }>--\n";
		cout << " a: Add Someone\n";
		if(!Managers.empty() || !Teachs.empty() || !Emps.empty())
			cout << " b: Remove Someone\n";
		cout << " c: Print Detail\n";
		cout << " f: Log out\n";
		cout << " >";
		cin >> opt;

		if (opt == 'a' || opt == 'c' || opt == 'f')
			valid = true;
		else if (opt == 'b' && (!Managers.empty() || !Teachs.empty() || !Emps.empty()))
			valid = true;
		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}

char Admin::printAddInterface()
{
	bool valid = false;
	char opt;
	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		cout << "\n --<{ Admin Controls }>--\n";
		cout << " a: Add Employee\n";
		cout << " b: Add Manager\n";
		cout << " c: Add Teacher\n";
		cout << " >";
		cin >> opt;

		if (opt == 'a' || opt == 'c' || opt == 'b')
			valid = true;

		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}

char Admin::printRemoveInterface()
{
	bool valid = false;
	char opt;
	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		cout << "\n --<{ Admin Controls }>--\n";
		if(!Emps.empty())
			cout << " a: Remove Employee\n";
		if (!Managers.empty())
			cout << " b: Remove Manager\n";
		if (!Teachs.empty())
			cout << " c: Remove Teacher\n";
		cout << " >";
		cin >> opt;

		if (opt == 'a' && !Emps.empty())
			valid = true;
		else if (opt == 'b' && !Managers.empty())
			valid = true;
		else if (opt == 'c' && !Teachs.empty())
			valid = true;
		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}

char Admin::printDetailInterface()
{
	bool valid = false;
	char opt;

	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Admin )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		cout << "\n --<{ Admin Controls }>--\n";
		cout << " a: Print Detail of Employees\n";
		cout << " b: Print Detail of Managers\n";
		cout << " c: Print Detail of Teachers\n";
		cout << " >";
		cin >> opt;

		if (opt == 'a' || opt == 'b' || opt == 'c')
			valid = true;

		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}

void Admin::control()
{
	Sleep(700);
	char opt = 'd';

	while (opt != 'f')
	{
		opt = printInterface();

		if (opt == 'a')
		{
			opt = printAddInterface();
			if (opt == 'a')
				addEmployee();
			else if (opt == 'b')
				addManager();
			else if (opt == 'c')
				addTeacher();
		}

		else if (opt == 'b')
		{
			opt = printRemoveInterface();
			if (opt == 'a')
				removeEmployee();
			else if (opt == 'b')
				removeManager();
			else if (opt == 'c')
				removeTeacher();
		}

		else if (opt == 'c')
		{
			opt = printDetailInterface();
			if (opt == 'a')
				displayEmployees();
			else if (opt == 'b')
				displayManagers();
			else if (opt == 'c')
				displayTeachers();
		}
		if(opt != 'f')
		{ 
			cin.ignore();
			cout << "\n Press any key to continue...";
			cin.get();
		}
	}
	cout << "\n Logging out...";
	Sleep(700);
	system("cls");
}

void Admin::displayEmployees()
{
	if (Emps.empty())
	{
		cout << "\n No Employee to Display\n";
		return ;
	}
	cout << "\n\t\t\t--<{ All Employees Detail}>--\n";

	for (int i = 0; i < Emps.size(); i++)
		Emps[i].printDetail();
}

void Admin::displayManagers()
{
	if (Managers.empty())
	{
		cout << "\n No Manager to Display\n";
		return;
	}
	cout << "\n\t\t\t--<{ All Managers Detail }>--\n";

	for (int i = 0; i < Managers.size(); i++)
		Managers[i].printDetail();
}

void Admin::displayTeachers()
{
	if (Teachs.empty())
	{
		cout << "\n No Teacher to Display\n";
		return;
	}
	cout << "\n\t\t\t--<{ All Teachers Detail }>--\n";

	for (int i = 0; i < Teachs.size(); i++)
		Teachs[i].printDetail();
}

void Admin::addEmployee()
{
	string nam;

	// Automatically generate a unique ID
	int id = Employee::getUniqueID();
	cin.ignore();
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

	cin.ignore();
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

	cin.ignore();
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
	cin.ignore();
	cout << "\n Enter Employee ID to remove: ";
	cin >> empId;
	Employee::markAsUnallocated(empId);
}

void Admin::removeTeacher() {
	int tId;
	cin.ignore();
	cout << "\n Enter Teacher ID to remove: ";
	cin >> tId;
	Teacher::markAsUnallocated(tId);
}

void Admin::removeManager() {
	int mId;
	cin.ignore();
	cout << "\n Enter Manager ID to remove: ";
	cin >> mId;
	Manager::markAsUnallocated(mId);
}

template<typename T>
void Admin::populateFromFile(const std::string& fileName, std::vector<T>& targetVector) {
	ifstream file(fileName);
	if (file.is_open()) {
		int id;
		string name;

		while (file >> id) {
			// Read the entire line as the name, including spaces
			getline(file >> ws, name);

			// Construct the item using the entire name
			T item(id, name);
			targetVector.push_back(item);
		}

		file.close();
	}
	else {
		cout << "Unable to open the file " << fileName << endl;
	}
}