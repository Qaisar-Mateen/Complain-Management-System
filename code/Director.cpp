#include "Director.h"
//#include"Department.h"

Director::Director(vector<Department>& d)
{
    id = 0;
    Name = "Director";
    depts = &d;
}

int Director::getID() const
{
    return id;
}

string Director::getName() const
{
    return Name;
}

void Director::control()
{
}

void Director::complains_in_Dept() {

}

void Director::complainsSummary() {

}

void Director::complainDetail() {

}