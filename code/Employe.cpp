#include "Employe.h"

Employe::Employe()
{
	id = -1;
}

Employe::Employe(int ID, string Name)
{
	id = ID;
	name = Name;
}

void Employe::printDetail()
{
	cout << "\n ID: " << id << "\t Name: " << name << "\n";
}

void Employe::updateSystem() 
{

}

Employe::~Employe()
{
}
