#include "Complaint.h"
#include "Teacher.h"
#include "Department.h"
#include "Global.h"

Complaint::Complaint(int ID, string des, int d, int t, int st, int day, int month, int year) : description(des), From(search(tea,t)), To(search(depts, d))
{
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

Complaint::Complaint(string des, int d, int t) : description(des), From(search(tea, t)), To(search(depts, d))
{
	id = getUniqueID();
    date = new Date();
	state = State::New;
    To->addComplaint(this);
    From->addComplaint(this);
    writeToFile(t, d);
}

void Complaint::setState(State s)
{
    state = s;
}

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
        file << id << ',' << description << ',' << t << ',' << d << ',' << date->getDay() << ',' << date->getMonth() << ',' << date->getYear() << ',' << st << endl;
        file.close();
    }
}
