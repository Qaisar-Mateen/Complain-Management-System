#include "Global.h"
#include "Person.h"
#include "Admin.h"
#include "Employee.h"
#include "Manager.h"
#include "Teacher.h"
#include "Director.h"

using namespace std;

Person* Login();

int main()
{
	init("Employee.txt", "Manager.txt", "Teacher.txt", "Department.txt", "Complaint.txt", "Job.txt");

	while (1) {
		Person* user = Login();
		if (user == nullptr)
			break;
		user->control();
	}
	return 0;
}

// Function to handle user login
Person* Login()
{
    char opt;
    bool valid = false;
    Person* p = nullptr;

    // Loop until a valid login is made
    while (!valid)
    {
        // Display login options
        cout << "\t\t\t\t ---<><><><><><><><><><( Login )><><><><><><><><><>---\n\n";
        cout << "\n Login as: (choose one from below)\n";
        if (adm)
            cout << " a: Admin\n";
        if (dir)
            cout << " b: Director\n";
        if (!man.empty())
            cout << " c: Manager\n";
        if (!tea.empty())
            cout << " d: Teacher\n";
        if (!emp.empty())
            cout << " e: Employee\n";
        cout << " q: Quit\n";
        cout << " >";
        cin >> opt;
        int id, f = 0;

        // Handle the selected option
        if (opt == 'q') // Quit
        {
            cout << "\n Closing Complain Management System!!\n";
            valid = true;
        }

        else if (opt == 'a' && adm) // Admin login
        {
            cout << "\t\t\t\t ---<><><><><><><><><><( Admin )><><><><><><><><><>---\n\n\n";
            cout << " Enter Admin's ID: ";
            cin >> id;
            // Loop until a valid ID is entered
            while (adm->getID() != id)
            {
                cout << "\n Invalid ID!!\n Enter Admin's ID: ";
                cin >> id;
            }
            cout << "\n You are now logged in as Admin \n";
            p = adm;
            valid = true;
        }

        else if (opt == 'b' && dir) // Director login
        {
            cout << "\t\t\t\t ---<><><><><><><><><><( Director )><><><><><><><><><>---\n\n\n";
            cout << " Enter Director's ID: ";
            cin >> id;
            // Loop until a valid ID is entered
            while (dir->getID() != id)
            {
                cout << "\n Invalid ID!!\n Enter Director's ID: ";
                cin >> id;
            }
            cout << "\n You are now logged in as Director\n";
            p = dir;
            valid = true;
        }

        // If the user chooses to log in as a manager and the list of managers is not empty
        else if (opt == 'c' && !man.empty())
        {
            // Print a header
            cout << "\t\t\t\t ---<><><><><><><><><><( Manager )><><><><><><><><><>---\n\n\n";
            cout << " Enter Manager's ID: ";
            // Loop until a valid ID is entered
            do {
                cin >> id;
                p = search(man, id); // Search for the manager with the entered ID
                if (p != nullptr) // If the manager is found, set the flag to 1
                    f = 1;
                if (f == 0) // If the manager is not found, print an error message and ask for the ID again
                    cout << "\n Invalid ID!!\n Enter Manager's ID: ";
            } while (f == 0);

            cout << "\n You are now logged in as Manager\n"; // Print a success message

            valid = true; // Set the valid flag to true
        }

        // If the user chooses to log in as a teacher and the list of teachers is not empty
        else if (opt == 'd' && !tea.empty())
        {
            // Print a header
            cout << "\t\t\t\t ---<><><><><><><><><><( Teacher )><><><><><><><><><>---\n\n\n";
            cout << " Enter Teacher's ID: ";
            // Loop until a valid ID is entered
            do {
                cin >> id;
                p = search(tea, id); // Search for the teacher with the entered ID
                if (p != nullptr) // If the teacher is found, set the flag to 1
                    f = 1;
                if (f == 0) // If the teacher is not found, print an error message and ask for the ID again
                    cout << "\n Invalid ID!!\n Enter Teacher's ID: ";

            } while (f == 0);

            cout << "\n You are now logged in as Teacher\n"; // Print a success message

            valid = true; // Set the valid flag to true
        }

        // If the user chooses to log in as an employee and the list of employees is not empty
        else if (opt == 'e' && !emp.empty())
        {
            // Print a header
            cout << "\t\t\t\t ---<><><><><><><><><><( Employee )><><><><><><><><><>---\n\n\n";
            cout << " Enter Employee's ID: ";
            // Loop until a valid ID is entered
            do {
                cin >> id;
                p = search(emp, id); // Search for the employee with the entered ID
                if (p != nullptr) // If the employee is found, set the flag to 1
                    f = 1;
                if (f == 0) // If the employee is not found, print an error message and ask for the ID again
                    cout << "\n Invalid ID!!\n Enter Employee's ID: ";

            } while (f == 0);

            cout << "\n You are now logged in as Employee\n"; // Print a success message
            valid = true; // Set the valid flag to true
        }

        // If the user enters an invalid option
        else
        {
            cout << "\n Invalid!!\n"; // Print an error message
            system("cls"); // Clear the console
        }
        Sleep(700); // Pause for 700 milliseconds

        return p; // Return the pointer to the logged-in user
    }
}