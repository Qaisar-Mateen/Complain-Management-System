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

// Function to read the job, it sets the Man_high to false and updates the file
void Job::read() { Man_high = false; updateFile(-1); }

// Function to get the ID of the job
int Job::getID() { return id; }

// Function to get the complaint ID of the job
int Job::getComID() { return com_id; }

// Function to get a unique ID for a new job
int Job::getUniqueID()
{
    ifstream file("Job.txt"); // Open the file
    int maxID = 1; // Initialize the maximum ID
    int currentID;
    // Read the file line by line
    while (file >> currentID) {
        file.ignore(); // Ignore the comma
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
        // If the current ID is equal to the maximum ID, increment the maximum ID
        if (currentID == maxID) {
            maxID++;
        }
    }
    file.close(); // Close the file
    return maxID; // Return the maximum ID
}

// Function to check if the job is completed
bool Job::isCompleted() { return completed; }

// Function to check if the job is highlighted
bool Job::isHighlight() { return Man_high; }

// Function to mark the job as complete or incomplete
void Job::Complete(bool t) {
    completed = Man_high = t; // Set the completed and Man_high flags to the passed value
    for (auto it : emps) // For each employee assigned to the job
        it->setAvailable(t); // Set their availability to the passed value
    updateFile(-1); // Update the file
}

// Function to print the details of the job
void Job::printDetail() {
    cout << "\n ID: " << id << "\t Complaint Id: " << com_id << "\t Assigned to: ";
    for (auto it : emps) // For each employee assigned to the job
        cout << it->getName() << ", "; // Print their name
    cout << "\t Assigned on ";
    date->displayDate(); // Display the date the job was assigned
    cout << (completed ? "\t Completed" : "\t Not Completed") << "\n"; // Print whether the job is completed or not
}

// Function to remove an employee from the job
void Job::removeEmp(Employee* e) {
    emps.erase(remove(emps.begin(), emps.end(), e), emps.end()); // Remove the employee from the list of assigned employees
    updateFile(e->getID()); // Update the file
}

// Function to write the job to a file
void Job::writeToFile() {
    ofstream file("Job.txt", ios::app); // Open the file in append mode
    if (file.is_open()) { // If the file is open
        file << id << ',' << com_id << ',' << man->getID() << ','; // Write the job's ID, complaint ID, and manager's ID
        for (int i = 0; i < emps.size(); i++) { // For each employee assigned to the job
            if (i == emps.size() - 1) // If it's the last employee
                file << emps[i]->getID() << ','; // Write their ID followed by a comma
            else
                file << emps[i]->getID() << ' '; // Otherwise, write their ID followed by a space
        }
        // Write the date, whether the job is completed, and whether it's highlighted
        file << date->getDay() << ',' << date->getMonth() << ',' << date->getYear() << ',' << (int)completed << ',' << (int)Man_high << endl;
        file.close(); // Close the file
    }
}

// Function to update the job in the file
void Job::updateFile(int emp_id = -1) {
    ifstream fileIn("Job.txt"); // Open the file for reading
    ofstream fileOut("Temp.txt"); // Open a temporary file for writing
    string line;

    // Read the file line by line
    while (getline(fileIn, line)) {
        if (!line.empty()) { // If the line is not empty
            istringstream iss(line); // Create a string stream from the line
            string field;
            getline(iss, field, ','); // Get the complaint ID
            int complaintId = stoi(field);

            // If the complaint ID matches the job's ID
            if (complaintId == id) {
                ostringstream oss; // Create an output string stream
                oss << id << ','; // Write the job's ID
                // Write the complaint ID, manager's ID, and employee IDs
                getline(iss, field, ',');  // complaint_id
                oss << field << ',';
                getline(iss, field, ',');  // manager_id
                oss << field << ',';

                // If an employee ID is passed
                if (emp_id != -1) {
                    // Process employee_ids
                    getline(iss, field, ',');
                    istringstream iss2(field);
                    string emp;
                    vector<int> empIds;
                    // Read the employee IDs
                    while (getline(iss2, emp, ' ')) {
                        int empId = stoi(emp);
                        // If the employee ID does not match the passed ID
                        if (empId != emp_id) {
                            empIds.push_back(empId); // Add it to the list
                        }
                    }
                    // If there are no employee IDs left
                    if (empIds.empty() && emp_id != -1) {
                        continue;     // Skip this row
                    }
                    // Write the employee IDs
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

                // Write the date, whether the job is completed, and whether it's highlighted
                getline(iss, field, ',');  // day
                oss << field << ',';
                getline(iss, field, ',');  // month
                oss << field << ',';
                getline(iss, field, ',');  // year
                oss << field << ',';
                oss << (int)completed << ',' << (int)Man_high;
                line = oss.str(); // Get the string from the output string stream
            }
            fileOut << line << '\n'; // Write the line to the temporary file
        }
    }
    fileIn.close(); // Close the input file
    fileOut.close(); // Close the output file

    remove("Job.txt");
    int chk = rename("Temp.txt", "Job.txt");
}