#include "Director.h"
//#include <windows.h>
#include <iostream>
#include "Date.h"

Director::Director(vector<Department*>& d)
{
    id = 0;
    Name = "Director";
	for (auto it : d)
		depts.push_back(it);
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
	char opt = 'd';

	while (opt != 'f')
	{
		opt = printInterface();

		if (opt == 'a') viewComplaintSummary();
		
		if (opt != 'f' && opt != 'l')
		{
			cin.ignore();
			cout << "\n Press any key to continue...";
			cin.get();
		}
	}
	cout << "\n Logging out...";
	Sleep(700);
	system("cls");
}

void Director::complains_in_Dept() {

}

void Director::viewComplaintSummary() {
	int startDay, startMonth, startYear, endDay, endMonth, endYear;
	while (true) {
		cout << "Enter the starting date (DDMMYYYY): ";
		int startDate;
		cin >> startDate;
		startDay = startDate / 1000000;
		startMonth = (startDate / 10000) % 100;
		startYear = startDate % 10000;
		if (startDay < 1 || startDay > 31 || startMonth < 1 || startMonth > 12) {
			cout << "Invalid date: Please enter a date in the format DDMMYYYY.\n";
			continue;
		}
		cout << "Enter the ending date (DDMMYYYY): ";
		int endDate;
		cin >> endDate;
		endDay = endDate / 1000000;
		endMonth = (endDate / 10000) % 100;
		endYear = endDate % 10000;
		if (endDay < 1 || endDay > 31 || endMonth < 1 || endMonth > 12) {
			cout << "Invalid: Please enter a date in the format DDMMYYYY.\n";
			continue;
		}
		if (endYear < startYear || (endYear == startYear && endMonth < startMonth) || (endYear == startYear && endMonth == startMonth && endDay < startDay)) {
			cout << "The ending date cannot be earlier than the starting date.\n";
			continue;
		}

		break;
	}
	Date st(startDay, startMonth, startYear), end(endDay, endMonth, endYear);
	system("cls");
	cout << "\t\t\t ----<><><><><><><><><><><><( Director )><><><><><><><><><><><>----\n\n";
	cout << " ID: " << id << endl;
	cout << " Name: " << Name << "\n\n";
	cout << " Summary of Complaints from ";
	st.displayDate();
	cout << " to ";
	end.displayDate();
	cout << "\n\n";
	for (auto it : depts)
		it->summary(st, end);
}

char Director::printInterface() {
	bool valid = false;
	char opt;

	do {
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Director )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		cout << "\n --<{ Director Controls }>--\n";
		cout << " a: View Complaint Summary\n";
		cout << " b: View Detail of Specific Complaint\n";
		cout << " l: Go Back\n";
		cout << " >";
		cin >> opt;

		if (opt == 'a' || opt == 'b' || opt == 'c' || opt == 'l')
			valid = true;

		else {
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);

	return opt;
}