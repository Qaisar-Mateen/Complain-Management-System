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

// Function to populate the Department from a file
void populateDepartment(string filename)
{
	ifstream file(filename); // Open the file
	if (!file.is_open()) { // If the file cannot be opened, print an error message and return
		cerr << "Error opening file." << endl;
		return;
	}

	string line;
	// Read the file line by line
	while (getline(file, line)) {
		// If the line is not empty, process it
		if (!line.empty()) {
			istringstream iss(line);
			int man_id, dept_id;
			vector<int> emp_id, comp_id;
			string name;

			// Parse the line
			iss >> dept_id >> ws; // Skip whitespaces
			getline(iss, name, '\'');
			iss >> man_id >> ws;

			// Skip the opening quote
			iss.ignore();
			int employee_id;
			// Read all employee IDs
			while (iss >> employee_id >> ws)
				emp_id.push_back(employee_id);

			// Search for the manager
			Manager* m = search(man, man_id);
			if (!m) { // If the manager does not exist, print an error message and exit
				cerr << "\n ERROR: Manager with id: " << man_id << " does not exists\n";
				exit(1);
			}

			// Check if all employees exist
			for (int i = 0; i < emp_id.size(); i++)
				if (!search(emp, emp_id[i])) { // If an employee does not exist, print an error message and exit
					cerr << "\n ERROR: Employee with id: " << emp_id[i] << " does not exists\n";
					exit(1);
				}

			// Add the department to the list
			depts.push_back(new Department(dept_id, name, m, emp_id));
		}
	}
	// Close the file
	file.close();
}

// Function to populate the Complaint from a file
void populateComplaint(string Filename) {

	ifstream file(Filename); // Open the file
	if (!file.is_open()) { // If the file cannot be opened, print an error message and return
		cerr << "Failed to open file\n";
		return;
	}
	string line;
	// Read the file line by line
	while (getline(file, line)) {
		// If the line is not empty, process it
		if (!line.empty()) {
			istringstream iss(line);
			string field;

			// Parse the line
			getline(iss, field, ','); //complaint_id
			int id = stoi(field);

			getline(iss, field, ','); //complaint Description
			string description = field;

			getline(iss, field, ','); //teacher id
			int teacher_Id = stoi(field);

			getline(iss, field, ','); //department id
			int dept_id = stoi(field);

			getline(iss, field, ','); //day 
			int day = stoi(field);

			getline(iss, field, ','); //month
			int month = stoi(field);

			getline(iss, field, ','); //year
			int year = stoi(field);

			getline(iss, field, ','); //complaint state
			int state = stoi(field);

			getline(iss, field, ','); //notify to teacher bool
			int noT = stoi(field);

			getline(iss, field, ','); //notify manager bool
			int nom = stoi(field);

			// Search for the department and teacher
			Department* d = search(depts, dept_id);
			Teacher* t = search(tea, teacher_Id);

			// If the department or teacher does not exist, print an error message and exit
			if (!d || !t) {
				cerr << "\n ERROR: Either a Teacher with id: " << teacher_Id << " or Department with id: " << dept_id << " does not exists!!\n";
				exit(1);
			}
			// Add the complaint to the list
			coms.push_back(new Complaint(id, description, dept_id, teacher_Id, state, day, month, year, noT, nom));
		}
	}
	// Close the file
	file.close();
}

// Function to populate the Job from a file
void populateJob(string Filename) {

	ifstream file(Filename); // Open the file
	if (!file.is_open()) { // If the file cannot be opened, print an error message and return
		cerr << "Failed to open file\n";
		return;
	}
	string line;
	// Read the file line by line
	while (getline(file, line)) {
		// If the line is not empty, process it
		if (!line.empty()) {
			istringstream iss(line);
			string field;

			// Parse the line
			getline(iss, field, ','); //job id
			int id = stoi(field);

			getline(iss, field, ','); //complaint id
			int com_Id = stoi(field);

			getline(iss, field, ','); //manager id
			int man_id = stoi(field);

			getline(iss, field, ','); //employee id list
			istringstream iss2(field);
			vector<int> empIds;
			// Read all employee IDs
			while (iss2 >> field)
				empIds.push_back(stoi(field));

			getline(iss, field, ','); //day 
			int day = stoi(field);

			getline(iss, field, ','); //month
			int month = stoi(field);

			getline(iss, field, ','); //year
			int year = stoi(field);

			getline(iss, field, ','); //complete bool
			int com = stoi(field);

			getline(iss, field, ','); //high priority bool
			int hi = stoi(field);

			// Search for the manager
			Manager* m = search(man, man_id);
			// Check if all employees exist
			for (int i = 0; i < empIds.size(); i++)
				if (!search(emp, empIds[i])) { // If an employee does not exist, print an error message and exit
					cerr << "\n ERROR: Employee with id: " << empIds[i] << " does not exists!!\n";
					exit(1);
				}

			// If the manager does not exist, set it to null
			if (!m) {
				m = nullptr;
			}

			// Add the job to the list
			jobs.push_back(new Job(id, com_Id, m, empIds, day, month, year, com, hi));
		}
	}
	// Close the file
	file.close();
}

// Function to populate the Employee from a file
void populateEmployee(string Filename) {

	ifstream file(Filename); // Open the file
	if (!file.is_open()) { // If the file cannot be opened, print an error message and return
		cerr << "Failed to open file\n";
		return;
	}

	string line;
	// Read the file line by line
	while (getline(file, line)) {
		// If the line is not empty, process it
		if (!line.empty()) {
			istringstream iss(line);
			string field;

			// Parse the line
			getline(iss, field, ','); // employee id
			int id = stoi(field);

			getline(iss, field, ','); // name
			string name = field;

			getline(iss, field, '\n'); // availability bool
			int aval = stoi(field);

			// Add the employee to the list
			emp.push_back(new Employee(id, name, (bool)aval));
		}
	}
	// Close the file
	file.close();
}


// Function to initialize the system with data from files
void init(string e_file, string m_file, string t_file, string d_file, string c_file, string j_file)
{
	// Create a new Admin object with the lists of employees, managers, and teachers
	adm = new Admin(emp, man, tea);

	// Populate the lists with data from the files
	populateEmployee(e_file); // Populate the list of employees
	populateFromFile(m_file, man); // Populate the list of managers
	populateFromFile(t_file, tea); // Populate the list of teachers

	populateDepartment(d_file); // Populate the list of departments
	populateComplaint(c_file); // Populate the list of complaints
	populateJob(j_file); // Populate the list of jobs

	// Create a new Director object with the list of departments
	dir = new Director(depts);
}