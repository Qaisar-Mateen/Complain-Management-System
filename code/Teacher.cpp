#include "Teacher.h"
#include "Complaint.h"
#include "Department.h"
#include "Global.h"

// Default constructor for the Teacher class
Teacher::Teacher()
{
    id = -1; // Initialize the ID to -1
    name = "Invalid"; // Initialize the name to "Invalid"
}

// Parameterized constructor for the Teacher class
Teacher::Teacher(int ID, string Name)
{
    id = ID; // Set the ID to the passed value
    name = Name; // Set the name to the passed value
}

// Function to control the teacher's actions
void Teacher::control()
{
    char opt = 'd'; // Initialize the option to 'd'

    // Loop until the option is 'f'
    while (opt != 'f')
    {
        opt = printInterface(); // Print the interface and get the user's option

        if (opt == 'a') makeComplaint(); // If the option is 'a', make a complaint

        else if (opt == 'b') complaintDetail(); // If the option is 'b', view the complaint details

        else if (opt == 'c') reocordFeedback(); // If the option is 'c', record feedback

        if (opt != 'f' && opt != 'l') // If the option is not 'f' or 'l'
        {
            cin.ignore(); // Ignore the newline character in the input buffer
            cout << "\n Press any key to continue..."; // Print a message
            cin.get(); // Wait for the user to press a key
        }
    }
    cout << "\n Logging out..."; // Print a message
    Sleep(700); // Pause for 700 milliseconds
    system("cls"); // Clear the console
}

// Function to print the teacher's interface and get the user's option
char Teacher::printInterface() {
    bool valid = false; // Initialize the valid flag to false
    char opt; // Declare a variable to hold the user's option
    do {
        int c = 0; // Initialize a flag to 0
        for (auto it : comps) // For each complaint
            if (it->notifyTeacher()) c = 1; // If the complaint notifies the teacher, set the flag to 1
        system("cls"); // Clear the console
        cout << "\t\t\t ----<><><><><><><><><><><><( Teacher )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << endl;
        cout << "\n --<{ Teacher Controls }>--\n";
        cout << " a: Make a Complaint\n"; // Print the option to make a complaint
        cout << " b: Display Complaints\n"; // Print the option to display complaints
        if (c) cout << " c: View pending FeedBack\n"; // If there are complaints that notify the teacher, print the option to view pending feedback
        cout << " f: Log out\n"; // Print the option to log out
        cout << " >";
        cin >> opt; // Get the user's option

        // If the option is valid, set the valid flag to true
        if (opt == 'a' || opt == 'b' || opt == 'f' || (c && opt == 'c'))
            valid = true;

        else { // If the option is not valid
            cout << "\n Invalid!! \n"; // Print a message
            Sleep(700); // Pause for 700 milliseconds
        }
    } while (!valid); // Repeat until the option is valid
    return opt; // Return the user's option
}


// Function to display the details of the teacher's complaints
void Teacher::complaintDetail() {
    if (comps.empty()) { // If there are no complaints
        cout << "\n No Complaints to Display\n"; // Print a message
        return; // Return
    }
    int opt; // Declare a variable to hold the user's option
    bool valid = false; // Initialize the valid flag to false
    do {
        system("cls"); // Clear the console
        cout << "\t\t\t ----<><><><><><><><><><><><( Teacher )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << "\n\n";
        cout << "\n\t\t\t--<{ All Complaints Detail }>--\n";
        for (int i = 0; i < comps.size(); i++) // For each complaint
            comps[i]->printDetail(); // Print the complaint's details

        cout << "\n\n Enter Complaint ID for Details: \n";
        cout << " 0: Go Back\n";
        cout << " >";
        cin >> opt; // Get the user's option
        Complaint* c = search(comps, opt); // Search for the complaint with the entered ID

        if (opt == 0) // If the option is 0
            valid = true; // Set the valid flag to true
        else if (c) { // If the complaint was found
            valid = true; // Set the valid flag to true
            c->printFullDetail(); // Print the full details of the complaint
        }

        else { // If the option is not valid
            cout << "\n Invalid!! \n"; // Print a message
            Sleep(700); // Pause for 700 milliseconds
        }

    } while (!valid); // Repeat until the option is valid
}

// Function to print the teacher's details
void Teacher::printDetail()
{
    cout << "\n ID: " << id << "\t Name: " << name << "\t Total Complaints Filed: " << comps.size() << "\n"; // Print the teacher's ID, name, and the number of complaints filed
}

void Teacher::makeComplaint() {
	string desc;
	int d_id;
	cout << "\n Enter Department ID for Complaint: ";
	cin >> d_id;
	if (!search(depts, d_id)) {
		cerr << "\n Invalid Department Id!!\n";
		return;
	}
	cin.ignore();
	cout << "\n Enter Complaint Description: ";
	getline(cin, desc);
	comps.push_back(new Complaint(desc, d_id, id));
	cout << "\n Complaint Filed successfully.\n";
}

void Teacher::reocordFeedback() {
    bool valid = false;
    int opt;
    do {
        vector<int> v;
        system("cls");
        cout << "\t\t\t ----<><><><><><><><><><><><( Teacher )><><><><><><><><><><><>----\n\n";
        cout << " ID: " << id << endl;
        cout << " Name: " << name << "\n\n";
        cout << "\n\t\t\t--<{ Pending FeedBacks }>--\n";
        for (int i = 0; i < comps.size(); i++)
            if (comps[i]->notifyTeacher()) { comps[i]->printDetail(); v.push_back(comps[i]->getID()); }

        if (v.empty()) {
            cout << "\n No Pending FeedBacks\n";
            valid = true;
        }
        else {
            cout << "\n\n Enter ID: \n";
            cout << " 0: Go Back\n";
            cout << " >";
            cin >> opt;
            int val = 0;

            for (int i = 0; i < v.size(); i++)
                if (v[i] == opt) val = 1;

            if (opt == 0) valid = true;

            else if (val) {
                valid = true;
                bool valid2 = false;
                do {
                    char op;
                    cout << " s: Satisfied\n";
                    cout << " n: Not Satisfied\n";
                    cout << " l: Go Back\n >";
                    cin >> op;
                    if (op == 'l') valid2 = true;

                    else if (op == 's') {
                        valid2 = true;
                        for (int i = 0; i < comps.size(); i++)
                            if (comps[i]->getID() == opt) {
                                comps[i]->setState(State::Closed);
                                comps[i]->setNotifyTea(false);
                            }
                    }

                    else if (op == 'n') {
                        valid2 = true;
                        for (int i = 0; i < comps.size(); i++)
                            if (comps[i]->getID() == opt) {
                                comps[i]->setNotifyTea(false);
                                comps[i]->setState(State::New);
                            }
                    }

                } while (!valid2);
            }

            else {
                cout << "\n Invalid!! \n";
                Sleep(700);
            }
        }
    } while (!valid);

}

void Teacher::writeToFile(const Teacher& teach) {
    ofstream file("Teacher.txt", ios::app);
    if (file.is_open()) {
        file << teach.getID() << " " << teach.getName() << endl;
        file.close();
    }
}

int Teacher::getUniqueID() {
    ifstream file("Teacher.txt");
    int maxID = 1;
    int currentID;

    while (file >> currentID) {
        file.ignore(); // Ignore the space between ID and name
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

        if (currentID == maxID) {
            maxID++;
        }
    }
    file.close();
    return maxID;
}

int Teacher::getID() const {return id;}

string Teacher::getName() const {return name;}

void Teacher::addComplaint(Complaint* c) {comps.push_back(c);}

void Teacher::markAsUnallocated(int teachId) {
    ifstream inFile("Teacher.txt");
    ofstream outFile("temp.txt");

    int currentID;
    string currentName;

    while (inFile >> currentID) {
        inFile.ignore(); // Ignore the space between ID and name
        getline(inFile, currentName); // Read the rest of the line, including spaces

        if (currentID == teachId) {
            // Unallocate Id
            outFile << "";
            cout << "\n Teacher with ID " << teachId << " removed successfully.\n";
        }
        else {
            outFile << currentID << " " << currentName << endl;
        }
    }
    inFile.close();
    outFile.close();

    // Rename the temp file to replace the original file
    remove("Teacher.txt");
    int chk = rename("temp.txt", "Teacher.txt");
}