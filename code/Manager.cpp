#include "Manager.h"

Manager::Manager()
{
	id = -1;
}

Manager::Manager(int ID, string Name)
{
	id = ID;
	name = Name;
}

void Manager::printDetail()
{
	cout << "\n ID: "<< id <<"\t Name: " << name<<"\n";
}

void Manager::reviewRequest() {

}

void Manager::assignJob() {

}

void Manager::reviewJob() {

}