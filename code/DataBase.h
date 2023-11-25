#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Admin.h"
#include "Manager.h"
#include "Employee.h"
#include "Teacher.h"
#include "Director.h"
#include "Department.h"

using namespace std;

class DataBase
{
	Director* dir;
	Admin* adm;
	vector<Employee> emp;
	vector<Manager> man;
	vector<Teacher> tea;
	vector<Department> dept;
public:

	DataBase()
	{
		adm = new Admin(emp, man, tea);
		dir = new Director();
	}

	template<typename t>
	t* search(vector<t>& per, int id)
	{
		for (int i = 0; i < per.size(); i++)
		{
			if (per[i].getID() == id)
				return &per[i];
		}

		return nullptr;
	}

	Admin* getAdmin()
	{
		return adm;
	}

	Director* getDirector()
	{
		return dir;
	}

	vector<Employee>* getEmployees()
	{
		return &emp;
	}

	vector<Manager>* getManagers()
	{
		return &man;
	}

	vector<Teacher>* getTeachers()
	{
		return &tea;
	}

	void init(string e_file, string m_file, string t_file, string d_file)
	{
		populateEmployee();
		populateManager();
		populateTeacher();
		populateDepartment(d_file);
	}

	void populateEmployee()
	{
		populateFromFile("Employee.txt", emp);
	}

	void populateManager()
	{
		populateFromFile("Manager.txt", man);
	}

	void populateTeacher()
	{
		populateFromFile("Teacher.txt", tea);
	}

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

			dept.push_back(Department(dept_id, name, search(man, man_id)));

			for (int i = 0; i < emp_id.size(); i++)
				dept.back().addEmployee(search(emp, emp_id[i]));
		}
		file.close();
	}

private:
	template<typename T>
	void populateFromFile(const std::string& fileName, std::vector<T>& targetVector) {
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
};