#include "Teacher.h"

Teacher::Teacher()
{
	id = -1;
}

Teacher::Teacher(int ID, string Name)
{
	id = ID;
	name = Name;
}

void Teacher::printDetail()
{
	cout << "\n ID: " << id << "\t Name: " << name << "\n";
}

void Teacher::makeComplain() {

}

void Teacher::printComplains() {

}

void Teacher::reocordFeedback() {

}