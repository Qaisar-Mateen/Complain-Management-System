#include "Complaint.h"
#include "Teacher.h"
#include "Department.h"
#include "Global.h"

//constructor for reading from file
// Constructor for the Complaint class
Complaint::Complaint(int ID, string des, int d, int t, int st, int day, int month, int year, int noT, int nom) : description(des), From(search(tea, t)), To(search(depts, d))
{
    // Convert integer values to boolean and assign to notify_m and notify_t
    notify_m = (bool)nom;
    notify_t = (bool)noT;
    // Assign ID to id
    id = ID;
    // Create a new Date object and assign to date
    date = new Date(day, month, year);
    // Switch case to assign the correct state based on the integer value st
    switch (st) {
    case 0:
        state = State::New;
        break;
    case 1:
        state = State::Assigned;
        break;
    case 2:
        state = State::Resolved;
        break;
    case 3:
        state = State::Closed;
        break;
    default:
        state = State::New;
        break;
    }
    // Add this complaint to the To and From objects
    To->addComplaint(this);
    From->addComplaint(this);
}

//constructor for new complaint
Complaint::Complaint(string des, int d, int t) : description(des), From(search(tea, t)), To(search(depts, d))
{
	id = getUniqueID();
    date = new Date();
	state = State::New;
    To->addComplaint(this);
    writeToFile(t, d);
    coms.push_back(this); //add to global
    notify_m = notify_t = false;
}

//getters
int Complaint::getID() { return id; }

State Complaint::getState() { return state; }

bool Complaint::notifyTeacher() { return notify_t; }
//setters
void Complaint::setState(State s)
{
    state = s;
    updateFile(state, notify_t, notify_m);
}

Date Complaint::getDate() { return *date; }

//some display functions
void Complaint::displayState()
{
    switch (state) {
        case State::New:
            cout<<"State: New";
            break;
        case State::Assigned:
            cout<<"State: Assigned";
            break;
        case State::Resolved:
            cout<<"State: Resolved";
            break;
        case State::Closed:
            cout<<"State: Closed";
            break;
    }
}

void Complaint::printDetail() {
    cout << "\n ID: " << id << "\t Description: " << description << "\t ";
    displayState();
    cout << "\n";
}

void Complaint::printFullDetail(){
    cout << "\n Complaint ID: " << id << "\t Filed To '" << To->getName() << "' Department by " << From->getName() << "\t On ";
    date->displayDate();
    cout << "\n ";
    displayState();
    cout << "\n Complaint Description: " << description << "\n";
}

int Complaint::getUniqueID() {
    ifstream file("Complaint.txt");
    int maxID = 1;
    int currentID;

    while (file >> currentID) {
        file.ignore(); // Ignore the space between ID and name
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

        if (currentID == maxID)
            maxID++;
    }
    file.close();

    return maxID;
}

void Complaint::setNotifyTea(bool t) { notify_t = t; updateFile(state, notify_t, notify_m); }

//function to write to file
void Complaint::writeToFile(int t, int d) {
    ofstream file("Complaint.txt", ios::app);
    if (file.is_open()) {
        int st;
        switch (state) {
        case State::New:
            st = 0;
            break;
        case State::Assigned:
            st = 1;
            break;
        case State::Resolved:
            st = 2;
            break;
        case State::Closed:
            st = 3;
            break;
        }
        file << id << ',' << description << ',' << t << ',' << d << ',' << date->getDay() << ',' << date->getMonth() << ',';
        file << date->getYear() << ',' << st << ',' << notify_t << ',' << notify_m << endl;
        file.close();
    }
}

// Function to update the complaint's state and notification settings in the file
void Complaint::updateFile(State newState, bool newNotifyTeacher, bool newNotifyManager) {
    // Open the file for reading
    ifstream fileIn("Complaint.txt");
    // Open a temporary file for writing
    ofstream fileOut("Temp.txt");
    string line;

    // Read the file line by line
    while (std::getline(fileIn, line)) {
        // Skip empty lines
        if (!line.empty()) {
            istringstream iss(line);
            string field;
            // Get the complaint ID
            getline(iss, field, ',');
            int complaintId = std::stoi(field);

            // If the complaint ID matches the current complaint's ID
            if (complaintId == id) {
                ostringstream oss;
                // Write the complaint ID
                oss << id << ',';
                // Copy the description, teacher ID, department ID, and date
                for (int i = 0; i < 6; ++i) {
                    getline(iss, field, ',');
                    oss << field << ',';
                }
                // Write the new state and notification settings
                oss << static_cast<int>(newState) << ',' << (int)newNotifyTeacher << ',' << (int)newNotifyManager;
                // Replace the line with the updated data
                line = oss.str();
            }
            // Write the line to the temporary file
            fileOut << line << '\n';
        }
    }
    // Close the files
    fileIn.close();
    fileOut.close();

    // Delete the original file
    remove("Complaint.txt");
    // Rename the temporary file to the original file's name
    int chk = rename("Temp.txt", "Complaint.txt");
}