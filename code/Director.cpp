#include "Director.h"
#include <iostream>
#include "Date.h"
#include "Global.h"
#include "Complaint.h"

// Director class constructor
Director::Director(vector<Department*>& d)
{
	id = 0;
	Name = "Director";
	for (auto it : d)
		depts.push_back(it);
}

// Getter for the director's ID
int Director::getID() const
{
	return id;
}

// Getter for the director's name
string Director::getName() const
{
	return Name;
}

// Function to control the director's actions
void Director::control()
{
	char opt = 'd';

	while (opt != 'f')
	{
		opt = printInterface();

		if (opt == 'a') viewComplaintSummary();

		else if (opt == 'b') complains_in_Dept();

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

// Function to display complaints in the department
void Director::complains_in_Dept() {
	int opt;
	bool valid = false;
	do {
		vector<int> v;
		system("cls");
		cout << "\t\t\t ----<><><><><><><><><><><><( Director )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << "\n\n";
		cout << "\n\t\t\t--<{ All Complaint's ID }>--\n";
		for (auto it : coms) {
			v.push_back(it->getID());
			cout << "\n ID: " << v.back();
		}

		cout << "\n\n Enter Complaint ID for Detail: \n";
		cout << " 0: Go Back\n";
		cout << " >";
		cin >> opt;
		Complaint* c = search(coms, opt); //get that complaint from search function

		if (opt == 0)
			valid = true;
		else if (c) {  //if user has selected a valid complaint id
			cin.ignore();
			c->printFullDetail();	//full detail about the complaint
			cout << "\n Press any key to continue...";
			cin.get();
		}
		else {	//incase of invalid option
			cout << "\n Invalid!! \n";
			Sleep(700);
		}

	} while (!valid);
}

// Function to view a summary of complaints within a specified date range
void Director::viewComplaintSummary() {
	int startDay, startMonth, startYear, endDay, endMonth, endYear;
	while (true) {
		// Prompt user to enter the start date
		cout << " Enter the starting date (DDMMYYYY): ";
		int startDate;
		cin >> startDate;
		// Extract day, month, and year from the entered date
		startDay = startDate / 1000000;
		startMonth = (startDate / 10000) % 100;
		startYear = startDate % 10000;
		// Validate the entered date
		if (startDay < 1 || startDay > 31 || startMonth < 1 || startMonth > 12) {
			cout << " Invalid date: Please enter a date in the format DDMMYYYY.\n";
			continue;
		}
		// Prompt user to enter the end date
		cout << " Enter the ending date (DDMMYYYY): ";
		int endDate;
		cin >> endDate;
		// Extract day, month, and year from the entered date
		endDay = endDate / 1000000;
		endMonth = (endDate / 10000) % 100;
		endYear = endDate % 10000;
		// Validate the entered date
		if (endDay < 1 || endDay > 31 || endMonth < 1 || endMonth > 12) {
			cout << " Invalid: Please enter a date in the format DDMMYYYY.\n";
			continue;
		}
		// Check if the end date is earlier than the start date
		if (endYear < startYear || (endYear == startYear && endMonth < startMonth) || (endYear == startYear && endMonth == startMonth && endDay < startDay)) {
			cout << " ERROR: The ending date cannot be earlier than the starting date.\n";
			continue;
		}

		break;
	}
	// Create Date objects for the start and end dates
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
	// Display a summary of complaints for each department within the specified date range
	for (auto it : depts)
		it->summary(st, end);
}

// Function to print the Director's interface and get the user's option
char Director::printInterface() {
	bool valid = false;
	char opt;

	do {
		// Clear the console
		system("cls");
		// Print the Director's details
		cout << "\t\t\t ----<><><><><><><><><><><><( Director )><><><><><><><><><><><>----\n\n";
		cout << " ID: " << id << endl;
		cout << " Name: " << Name << endl;
		// Print the available options
		cout << "\n --<{ Director Controls }>--\n";
		cout << " a: View Complaint Summary\n";
		cout << " b: View Detail of Specific Complaint\n";
		cout << " f: Log Out\n";
		cout << " >";
		// Get the user's option
		cin >> opt;

		// Validate the user's option
		if (opt == 'a' || opt == 'b' || opt == 'f')
			valid = true;
		else {
			// Print an error message if the user's option is invalid
			cout << "\n Invalid!! \n";
			Sleep(700);
		}
	} while (!valid);  // Repeat until the user's option is valid

	// Return the user's option
	return opt;
}