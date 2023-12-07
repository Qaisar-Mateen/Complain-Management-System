#include "Complaint.h"
#include "Teacher.h"
#include "Department.h"
#include "Global.h"

//constructor for reading from file
Complaint::Complaint(int ID, string des, int d, int t, int st, int day, int month, int year, int noT, int nom) : description(des), From(search(tea,t)), To(search(depts, d))
{
    notify_m = (bool)nom;
    notify_t = (bool)noT;
    id = ID;
    date = new Date(day, month, year);
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

//function to update the file data to the latest
void Complaint::updateFile(State newState, bool newNotifyTeacher, bool newNotifyManager) {
    ifstream fileIn("Complaint.txt");
    ofstream fileOut("Temp.txt");
    string line;

    while (std::getline(fileIn, line)) {
        if (!line.empty()) {
            istringstream iss(line);
            string field;
            getline(iss, field, ',');
            int complaintId = std::stoi(field);

            if (complaintId == id) {
                ostringstream oss;
                oss << id << ',';
                getline(iss, field, ',');  // Description
                oss << field << ',';
                getline(iss, field, ',');  // teacher_id
                oss << field << ',';
                getline(iss, field, ',');  // dept_id
                oss << field << ',';
                getline(iss, field, ',');  // day
                oss << field << ',';
                getline(iss, field, ',');  // month
                oss << field << ',';
                getline(iss, field, ',');  // year
                oss << field << ',';
                oss << static_cast<int>(newState) << ',' << (int)newNotifyTeacher << ',' << (int)newNotifyManager;
                line = oss.str();
            }
            fileOut << line << '\n';
        }
    }
    fileIn.close();
    fileOut.close();

    remove("Complaint.txt");
    int chk = rename("Temp.txt", "Complaint.txt");
}