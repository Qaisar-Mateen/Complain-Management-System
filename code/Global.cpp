#include "Global.h"
#include "Admin.h"
#include "Department.h"
#include "Employee.h"
#include "Manager.h"
#include "Teacher.h"
#include "Complaint.h"
#include "Director.h"
#include "Job.h"

using namespace std;

Director* dir;
Admin* adm;
vector<Employee*> emp;
vector<Manager*> man;
vector<Teacher*> tea;
vector<Department*> depts;
vector<Complaint*> coms;
vector<Job*> jobs;

void populateDepartment(string filename)
{
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Error opening file." << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			istringstream iss(line);
			int man_id, dept_id;
			vector<int> emp_id, comp_id;
			string name;

			iss >> dept_id >> ws; // Skip whitespaces
			getline(iss, name, '\'');
			iss >> man_id >> ws;

			iss.ignore(); // Skip the opening quote
			int employee_id;
			while (iss >> employee_id >> ws)
				emp_id.push_back(employee_id);

			Manager* m = search(man, man_id);
			if (!m) {
				cerr << "\n ERROR: Manager with id: " << man_id << " does not exists\n";
				exit(1);
			}

			for (int i = 0; i < emp_id.size(); i++)
				if (!search(emp, emp_id[i])) {
					cerr << "\n ERROR: Employee with id: " << emp_id[i] << " does not exists\n";
					exit(1);
				}

			depts.push_back(new Department(dept_id, name, m, emp_id));
		}
	}
	file.close();
}

void populateComplaint(string Filename) {

	ifstream file(Filename);
	if (!file.is_open()) {
		cerr << "Failed to open file\n";
		return;
	}
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			istringstream iss(line);
			string field;

			getline(iss, field, ','); //complaint_id
			int id = stoi(field);

			getline(iss, field, ','); //complaint Description
			string description = field;

			getline(iss, field, ',');
			int teacher_Id = stoi(field); //teacher id

			getline(iss, field, ',');	//department id
			int dept_id = stoi(field);

			getline(iss, field, ',');
			int day = stoi(field); //day 

			getline(iss, field, ',');
			int month = stoi(field); //month

			getline(iss, field, ',');
			int year = stoi(field); //year

			getline(iss, field, ',');
			int state = stoi(field); //complaint state

			getline(iss, field, ',');
			int noT = stoi(field);	//notify to teacher bool

			getline(iss, field, ',');
			int nom = stoi(field); //notify manager bool

			Department* d = search(depts, dept_id);
			Teacher* t = search(tea, teacher_Id);

			if (!d || !t) {
				cerr << "\n ERROR: Either a Teacher with id: " << teacher_Id << " or Department with id: " << dept_id << " does not exists!!\n";
				exit(1);
			}
			coms.push_back(new Complaint(id, description, dept_id, teacher_Id, state, day, month, year, noT, nom));
		}
	}
	file.close();
}

void populateJob(string Filename) {
	
	ifstream file(Filename);
	if (!file.is_open()) {
		cerr << "Failed to open file\n";
		return;
	}
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			istringstream iss(line);
			string field;

			getline(iss, field, ',');
			int id = stoi(field);	//job id

			getline(iss, field, ',');
			int com_Id = stoi(field);	//complaint id

			getline(iss, field, ',');
			int man_id = stoi(field);	//manager id

			getline(iss, field, ',');	//employee id list
			istringstream iss2(field);
			vector<int> empIds;
			while (iss2 >> field)
				empIds.push_back(stoi(field));

			getline(iss, field, ',');
			int day = stoi(field);	

			getline(iss, field, ',');
			int month = stoi(field);

			getline(iss, field, ',');
			int year = stoi(field);

			getline(iss, field, ',');
			int com = stoi(field);	//complete bool

			getline(iss, field, ',');
			int hi = stoi(field);

			Manager* m = search(man, man_id);
			for (int i = 0; i < empIds.size(); i++)
				if (!search(emp, empIds[i])) {
					cerr << "\n ERROR: Employee with id: " << empIds[i] << " does not exists!!\n";
					exit(1);
				}

			if (!m) {
				m = nullptr;
				//cerr << "\n ERROR: Manager with id: " << man_id << " does not exists!!\n";
				//exit(1);
			}
 
			jobs.push_back(new Job(id, com_Id, m, empIds, day, month, year, com, hi));
		}
	}
	file.close();
}

void populateEmployee(string Filename) {

	ifstream file(Filename);
	if (!file.is_open()) {
		cerr << "Failed to open file\n";
		return;
	}
	
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			istringstream iss(line);
			string field;

			getline(iss, field, ',');
			int id = stoi(field);	// emp id

			getline(iss, field, ',');
			string name = field;	//name
	
			getline(iss, field, '\n');
			int aval = stoi(field);	//availability bool

			emp.push_back(new Employee(id, name, (bool)aval));
		}
	}
	file.close();
}

void init(string e_file, string m_file, string t_file, string d_file, string c_file, string j_file)
{
	adm = new Admin(emp, man, tea);

	populateEmployee(e_file);
	populateFromFile(m_file, man);
	populateFromFile(t_file, tea);

	populateDepartment(d_file);
	populateComplaint(c_file);
	populateJob(j_file);
	dir = new Director(depts);
}