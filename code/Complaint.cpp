#include "Complaint.h"
#include "Teacher.h"
#include "Department.h"
#include "Global.h"

Complaint::Complaint(int ID, string des, Department* d, Teacher* teacher, int st, int day, int month, int year) : description(des), From(teacher), To(d)
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
    }

    d->addComplaint(this);
//    teacher.
}

Complaint::Complaint(string des, int d_id, Teacher* teacher) : description(des), From(teacher)
{
	id = getUniqueID();
	To = search(depts, d_id);
    date = new Date();
	state = State::New;
    To->addComplaint(this);
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


void Complaint::currState() {

}

void Complaint::changeState() {

}

void Complaint::printDetail() {

}

int Complaint::getUniqueID() {
    ifstream file("Complaint.txt");
    int maxID = 0;
    int currentID;

    while (file >> currentID) {
        file.ignore(); // Ignore the space between ID and name
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

        if (currentID > maxID) {
            maxID = currentID;
        }
    }

    file.close();

    return maxID + 1;
}