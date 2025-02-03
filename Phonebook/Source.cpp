#include<iostream>
#include <fstream>
#include <string>
using namespace std;

const int Max_no_of_contacts = 10;

struct Contact
{
    string name;
    string number;
};

Contact phonebook[Max_no_of_contacts];
int Number_of_Contacts = 0;

// Function prototypes
void addContact();
void updateContact();
void deleteContact();
void searchContact();
void listContacts();
void savePhonebookToFile();
void loadPhonebookFromFile();
void deleteAllDataFromFile();

int main()
{
    // Load phonebook from file at the beginning
    loadPhonebookFromFile();

    string choice;

    while (true)
    {
        cout << "_\n\n";
        cout << " \t \t \t \t     HELLO TO YOUR PHONEBOOK     \t \t \n";
        cout << "_\n\n";
        cout << "1. ADD NEW CONTACT " << endl;
        cout << "2. UPDATE" << endl;
        cout << "3. DELETE" << endl;
        cout << "4. RETRIEVE" << endl;
        cout << "5. SHOW ALL DATA " << endl;
        cout << "6. DELETE ALL CONTACTS" << endl; // New option to delete all data from the file
        cout << "7. EXIT " << endl;
        cout << "Enter your choice: ";

        getline(cin, choice); // Read the entire line, including spaces

        if (choice == "1" || choice == "ADD" || choice == "NEW" || choice == "CONTACT")
        {
            addContact();
        }
        else if (choice == "2" || choice == "UPDATE")
        {
            updateContact();
        }
        else if (choice == "3" || choice == "DELETE")
        {
            deleteContact();
        }
        else if (choice == "4" || choice == "RETRIEVE")
        {
            searchContact();
        }
        else if (choice == "5" || choice == "SHOW ALL DATA")
        {
            listContacts();
        }
        else if (choice == "6" || choice == "DELETE ALL CONTACTS") // Handle delete all data from file
        {
            deleteAllDataFromFile(); // Call the function to delete all data from the file
            break;
        }
        else if (choice == "7" || choice == "EXIT") {
            string confirm;
            cout << "Are you sure you want to exit? (YES/NO): ";
            cin >> confirm;
            if (confirm == "YES")
            {
                cout << "Saving phonebook and ending..." << endl;
                savePhonebookToFile(); // Save phonebook to file before quitting
                break; // Exit the loop
            }
            else if (confirm == "NO")
            {
                cout << "Continuing the program." << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
            }
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }

    }
    return 0;
}

void addContact()
{
    if (Number_of_Contacts >= Max_no_of_contacts) {
        cout << "Phonebook is full. Cannot add more contacts." << endl;
        return;
    }

    cout << "Enter name: ";
    string name;
    getline(cin, name); // Read the entire line, including spaces

    // Check if the contact name is already in the system
    for (int i = 0; i < Number_of_Contacts; i++) {
        if (phonebook[i].name == name) {
            cout << "Contact is already in the system." << endl;
            return;
        }
    }

    cout << "Enter PhoneNumber: ";
    string number;
    getline(cin, number); // Read the entire line, including spaces

    // Check if the phone number is empty
    if (number.empty()) {
        cout << "Wrong Input" << endl;
        return;
    }

    // Validate if the phone number contains only digits
    for (char c : number) {
        if (!isdigit(c)) {
            cout << "Wrong Input" << endl;
            return;
        }
    }

    phonebook[Number_of_Contacts].name = name; // Assign the name after validation
    phonebook[Number_of_Contacts].number = number; // Assign the number after validation
    Number_of_Contacts++;
    cout << "Contact added successfully." << endl;

    // Save the updated phonebook to the file
    savePhonebookToFile();
}


void updateContact()
{
    string name;
    cout << "Enter the name of the contact to modify: ";
    getline(cin, name); // Read the entire line, including spaces

    bool contactFound = false;
    for (int i = 0; i < Number_of_Contacts; i++)
    {
        if (phonebook[i].name == name)
        {
            cout << "Enter new number: ";
            getline(cin, phonebook[i].number); // Read the entire line, including spaces

            // Check if the phone number is empty
            if (phonebook[i].number.empty()) {
                cout << "Wrong Input" << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
                return;
            }

            // Validate if the phone number contains only digits
            bool numberValid = true;
            for (char c : phonebook[i].number) {
                if (!isdigit(c)) {
                    numberValid = false;
                    break;
                }
            }

            if (!numberValid) {
                cout << "Wrong Input" << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
                return;
            }

            cout << "Contact modified successfully." << endl;
            contactFound = true;
            break;
        }
    }

    if (!contactFound)
    {
        string option;
        cout << "Contact not found. Would you like to add it? (YES/NO): ";
        cin >> option;
        cin.ignore(); // Clear the input buffer
        if (option == "YES")
        {
            addContact(); // Call the addContact() function to add a new contact
        }
        else if (option == "NO")
        {
            cout << "The contact has not been added." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter YES or NO." << endl;
        }
    }
}



void deleteContact()
{
    string name;
    cout << "Enter the name of the contact to delete: ";
    getline(cin, name); // Read the entire line, including spaces

    for (int i = 0; i < Number_of_Contacts; i++)
    {
        if (phonebook[i].name == name)
        {
            for (int j = i; j < Number_of_Contacts - 1; j++)
            {
                phonebook[j] = phonebook[j + 1];
            }
            Number_of_Contacts--;
            cout << "Contact deleted successfully." << endl;

            // Save the updated phonebook to the file
            savePhonebookToFile();
            return;
        }
    }

    cout << "Contact is not on the system. " << endl;
}

void searchContact()
{
    string search;
    cout << "Enter the name or number to search: ";
    getline(cin, search); // Read the entire line, including spaces

    for (int i = 0; i < Number_of_Contacts; i++)
    {
        if (phonebook[i].name == search || phonebook[i].number == search)
        {
            cout << "Contact found: " << endl;
            cout << "Name: " << phonebook[i].name << ", Number: " << phonebook[i].number << endl;
            return;
        }
    }

    cout << "Contact is not on the system." << endl;
}

void listContacts()
{
    if (Number_of_Contacts == 0)
    {
        cout << "Phonebook is empty." << endl;
        exit(0);
    }
    cout << "ALL CONTACTS: \n";

    for (int i = 0; i < Number_of_Contacts; i++) {
        cout << phonebook[i].name << " " << phonebook[i].number << endl;
    }

    // Add a break statement to exit the program after showing all data
    cout << "Exiting the program." << endl;
    exit(0);
}


void savePhonebookToFile()
{
    ofstream outfile("phonebook.txt");
    if (outfile.is_open())
    {
        for (int i = 0; i < Number_of_Contacts; i++)
        {
            outfile << phonebook[i].name << " " << phonebook[i].number << endl;
        }
        outfile.close(); // Close the file stream
    }
    else
    {
        cout << "Unable to open the file for saving." << endl;
    }
}

void loadPhonebookFromFile()
{
    ifstream infile("phonebook.txt");
    if (infile.is_open())
    {
        Number_of_Contacts = 0; // Reset the number of contacts
        string name, number;
        while (infile >> name >> number)
        {
            phonebook[Number_of_Contacts].name = name;
            phonebook[Number_of_Contacts].number = number;
            Number_of_Contacts++;
            if (Number_of_Contacts >= Max_no_of_contacts) // Avoid exceeding the array size
                break;
        }
        infile.close(); // Close the file stream
    }
    else
    {
        cout << "No existing phonebook file found. Starting with an empty phonebook." << endl;
    }
}

void deleteAllDataFromFile()
{
    if (remove("phonebook.txt") == 0) // Attempt to delete the file
    {
        cout << "All data has been deleted successfully." << endl;
    }
    else
    {
        cout << "Unable to delete data file." << endl;
    }
}