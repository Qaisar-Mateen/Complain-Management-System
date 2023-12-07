#include "Job.h"
#include "Date.h"
#include "Manager.h"
#include "Employee.h"
#include "Complaint.h"
#include "Global.h"

// Constructor for creating a new job
Job::Job(int c_id, Manager* m, vector<int> e) : com_id(c_id), man(m) {
    id = getUniqueID();  // Generate a unique ID for the job
    for (int i = 0; i < e.size(); i++) {
        emps.push_back(search(emp, e[i]));  // Add employees to the job
        emps.back()->addJob(this);  // Add this job to the last added employee's job list
    }
    date = new Date();  // Set the date to the current date
    jobs.push_back(this);  
    Man_high = completed = false;
    writeToFile();  // Write the job details to file
}

// Constructor for creating a job from file data
Job::Job(int iD, int c_id, Manager* m, vector<int> e, int day, int month, int year, int com, int hi): com_id(c_id), man(m) {
    id = iD;
    completed = (bool)com;
    Man_high = (bool)hi;
    for (int i = 0; i < e.size(); i++) {
        emps.push_back(search(emp, e[i]));
        emps.back()->addJob(this);  
    }
    date = new Date(day, month, year);  // Set the date to the given date
    if (m != nullptr)
        man->addJob(this);  // Add this job to the manager's job list
}

void Job::read() { Man_high = false; updateFile(-1); }

int Job::getID() { return id; }

int Job::getComID() { return com_id; }

int Job::getUniqueID()
{
	ifstream file("Job.txt");
	int maxID = 1;
	int currentID;
	while (file >> currentID) {
		file.ignore();
		file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
		if (currentID == maxID) {
			maxID++;
		}
	}
	file.close();
	return maxID;
}

bool Job::isCompleted() { return completed; }

bool Job::isHighlight() { return Man_high; }

void Job::Complete(bool t) { 
	completed = Man_high = t; 
	for (auto it : emps)
		it->setAvailable(t);
	updateFile(-1);
}

void Job::printDetail(){
	cout << "\n ID: " << id << "\t Complaint Id: " << com_id << "\t Assigned to: ";
	for (auto it : emps)
		cout << it->getName() << ", ";
	cout << "\t Assigned on ";
	date->displayDate();
	cout << (completed? "\t Completed" : "\t Not Completed") << "\n";
}

void Job::removeEmp(Employee* e) {
	emps.erase(remove(emps.begin(), emps.end(), e), emps.end());
	updateFile(e->getID());
}

void Job::writeToFile() {
	ofstream file("Job.txt", ios::app);
	if (file.is_open()) {
		file << id << ',' << com_id << ',' << man->getID() << ',';
		for (int i = 0; i < emps.size(); i++) {
			if(i == emps.size()-1)
				file << emps[i]->getID() << ',';
			else
				file << emps[i]->getID() << ' ';
		}
		file << date->getDay() << ',' << date->getMonth() << ',' << date->getYear() << ',' << (int)completed << ',' << (int)Man_high << endl;
		file.close();
	}
}

void Job::updateFile(int emp_id = -1) {
    ifstream fileIn("Job.txt");
    ofstream fileOut("Temp.txt");
    string line;

    while (getline(fileIn, line)) {
        if (!line.empty()) {
            istringstream iss(line);
            string field;
            getline(iss, field, ',');
            int complaintId = stoi(field);

            if (complaintId == id) {
                ostringstream oss;
                oss << id << ',';
                getline(iss, field, ',');  // complaint_id
                oss << field << ',';
                getline(iss, field, ',');  // manager_id
                oss << field << ',';
				
				if(emp_id != -1) {
                	// Process employee_ids
                	getline(iss, field, ',');
                	istringstream iss2(field);
                	string emp;
                	vector<int> empIds;
                	while (getline(iss2, emp, ' ')) {
                    	int empId = stoi(emp);
	                    if (empId != emp_id) {
                        	empIds.push_back(empId);
	                    }
                	}
					if (empIds.empty() && emp_id != -1) {
                 		continue;     // Skip this row if there are no employee IDs left
                	}
					for (size_t i = 0; i < empIds.size(); ++i) {
                    	if (i > 0) {
	                        oss << ' ';
                    	}
                    	oss << empIds[i];
                	}
                	oss << ',';
				}

				else { //no need to delete employee in this case
					oss << field << ',';
            		getline(iss, field, ',');  // employee_ids
				}
            
                getline(iss, field, ',');  // day
                oss << field << ',';
                getline(iss, field, ',');  // month
                oss << field << ',';
                getline(iss, field, ',');  // year
                oss << field << ',';
                oss << (int)completed << ',' << (int)Man_high;
                line = oss.str();
            }
            fileOut << line << '\n';
        }
    }
    fileIn.close();
    fileOut.close();

    remove("Job.txt");
    int chk = rename("Temp.txt", "Job.txt");
}