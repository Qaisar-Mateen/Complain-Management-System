#include "Global.h"
#include "Admin.h"
#include "Department.h"
#include "Employee.h"
#include "Manager.h"
#include "Teacher.h"
#include "Complaint.h"
#include "Director.h"

using namespace std;

Director* dir;
Admin* adm;
vector<Employee> emp;
vector<Manager> man;
vector<Teacher> tea;
vector<Department> depts;

void populateDepartment(string filename)
{
	ifstream file(filename);

	if (!file.is_open()) {
		cerr << "Error opening file." << endl;
		return;
	}

	string line;
	while (getline(file, line))
	{
		istringstream iss(line);
		int man_id, dept_id;
		vector<int> emp_id, comp_id;
		string name;

		iss >> dept_id >> ws; // Skip whitespaces
		getline(iss, name, '\'');
		iss >> man_id >> ws;

		// Process the employee ids
		iss.ignore(); // Skip the opening quote
		int employee_id;
		while (iss >> employee_id >> ws)
			emp_id.push_back(employee_id);

		Manager* m = search(man, man_id);
		if (!m) {
			cerr << "\n ERROR: Manager with id: " << man_id << " does not exists\n";
			exit(1);
		}
		Department *d = new Department(dept_id, name, m);
		depts.push_back(*d);

		for (int i = 0; i < emp_id.size(); i++) {
			Employee* e = search(emp, emp_id[i]);
			if (e) {
				depts.back().addEmployee(e);			
				e->addDept(d);
			}
			else {
				cerr << "\n ERROR: Employee with id: " << emp_id[i] << " does not exists\n";
				exit(1);
			}
		}
	}
	file.close();
}

void init(string e_file, string m_file, string t_file, string d_file)
{
	adm = new Admin(emp, man, tea);
	dir = new Director(depts);

	populateFromFile(e_file, emp);
	populateFromFile(m_file, man);
	populateFromFile(t_file, tea);

	populateDepartment(d_file);
}