#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <iomanip>

using namespace std;

// ============================================================
// Basic struct to hold customer data
// ============================================================
struct Customer {
    string roomnumber;
    string name;
    string address;
    string phonenumber;
    string nationality;
    string email;
    string period;
    string arrivaldate;
};


// ============================================================
// Base Class
// Demonstrates INHERITANCE
// ============================================================
class FileManager {
protected:
    string filename;

public:
    // Constructor
    FileManager() {
        filename = "customers.txt";
    }

    // Destructor
    ~FileManager() {
        // No file remains open because files are opened and
        // closed inside individual member functions.
    }
};


// ============================================================
// Derived Class
// HotelManager inherits from FileManager
// ============================================================
class HotelManager : public FileManager {

private:

    // Helper function to check if a room is already booked
    bool roomExists(string room) {
        ifstream file(filename);
        Customer c;

        // Read file line by line using '|' as delimiter
        while (getline(file, c.roomnumber, '|')) {
            getline(file, c.name, '|');
            getline(file, c.address, '|');
            getline(file, c.phonenumber, '|');
            getline(file, c.nationality, '|');
            getline(file, c.email, '|');
            getline(file, c.period, '|');
            getline(file, c.arrivaldate);

            if (c.roomnumber == room) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }


    // Helper to print table header neatly
    void printHeader() {
        cout << left << setw(7) << "ROOM"
             << setw(15) << "NAME"
             << setw(15) << "ADDRESS"
             << setw(15) << "PHONE"
             << setw(13) << "NATIONALITY"
             << setw(22) << "EMAIL"
             << setw(10) << "PERIOD"
             << setw(15) << "ARRIVAL" << "\n";
    }


    // Helper to print a single customer neatly
    void printCustomer(const Customer& c) {
        cout << left << setw(7) << c.roomnumber
             << setw(15) << c.name
             << setw(15) << c.address
             << setw(15) << c.phonenumber
             << setw(13) << c.nationality
             << setw(22) << c.email
             << setw(10) << c.period
             << setw(15) << c.arrivaldate << "\n";
    }


public:

    // ========================================================
    // CONSTRUCTOR
    // ========================================================
    HotelManager() : FileManager() {
        cout << "Hotel Manager initialized.\n";
    }


    // ========================================================
    // DESTRUCTOR
    // ========================================================
    ~HotelManager() {
        cout << "Hotel Manager closed.\n";
    }


    // ========================================================
    // ADD CUSTOMER
    // ========================================================
    void addCustomer() {

    string continueAdding;

    do {

        Customer c;

        // Keep asking until an available room is entered
        while (true) {

            cout << "Enter Room Number: ";
            getline(cin, c.roomnumber);

            if (roomExists(c.roomnumber)) {

                cout << "Error: Room number " << c.roomnumber
                     << " is already booked!\n";
                cout << "Please enter another room number.\n\n";
            }
            else {
                break;
            }
        }

        cout << "Enter Full Name: ";
        getline(cin, c.name);

        cout << "Enter Address: ";
        getline(cin, c.address);

        cout << "Enter Phone Number: ";
        getline(cin, c.phonenumber);

        cout << "Enter Nationality: ";
        getline(cin, c.nationality);

        cout << "Enter Email: ";
        getline(cin, c.email);

        cout << "Enter Period (days): ";
        getline(cin, c.period);

        cout << "Enter Arrival Date (dd-mm-yyyy): ";
        getline(cin, c.arrivaldate);

        // Open file in append mode
        ofstream file(filename, ios::app);

        if (file.is_open()) {

            file << c.roomnumber << "|"
                 << c.name << "|"
                 << c.address << "|"
                 << c.phonenumber << "|"
                 << c.nationality << "|"
                 << c.email << "|"
                 << c.period << "|"
                 << c.arrivaldate << "\n";

            file.close();

            cout << "----------------------------\n";
            cout << "Customer added successfully!\n";
            cout << "----------------------------\n";

        }
        else {

            cout << "Error: could not open data file.\n";
            return;
        }

        // Ask whether to add another customer
        while (true) {

            cout << "\nDo you want to add another customer? (y/n): ";
            getline(cin, continueAdding);

            if (continueAdding == "y" ||
                continueAdding == "Y" ||
                continueAdding == "n" ||
                continueAdding == "N") {

                break;
            }

            cout << "Invalid input! Please enter y or n.\n";
        }

        cout << "\n";

    } while (continueAdding == "y" || continueAdding == "Y");
}


    // ========================================================
    // DISPLAY CUSTOMERS
    // ========================================================
    void displayCustomers() {

        ifstream file(filename);

        if (!file.is_open()) {
            cout << "No customers found.\n";
            return;
        }

        string sep(113, '-');

        cout << sep << "\n";
        printHeader();
        cout << sep << "\n";

        Customer c;
        bool found = false;

        while (getline(file, c.roomnumber, '|')) {

            getline(file, c.name, '|');
            getline(file, c.address, '|');
            getline(file, c.phonenumber, '|');
            getline(file, c.nationality, '|');
            getline(file, c.email, '|');
            getline(file, c.period, '|');
            getline(file, c.arrivaldate);

            found = true;

            printCustomer(c);
        }

        if (!found) {
            cout << "No customers found.\n";
        }

        cout << sep << "\n";

        file.close();
    }


    // ========================================================
    // SEARCH CUSTOMER
    // ========================================================
    void searchCustomer(string room) {

        ifstream file(filename);
        Customer c;

        while (getline(file, c.roomnumber, '|')) {

            getline(file, c.name, '|');
            getline(file, c.address, '|');
            getline(file, c.phonenumber, '|');
            getline(file, c.nationality, '|');
            getline(file, c.email, '|');
            getline(file, c.period, '|');
            getline(file, c.arrivaldate);

            if (c.roomnumber == room) {

                string sep(113, '-');

                cout << "Customer found:\n";
                cout << sep << "\n";

                printHeader();

                cout << sep << "\n";

                printCustomer(c);

                cout << sep << "\n";

                file.close();

                return;
            }
        }

        cout << "Customer with room number "
             << room << " not found.\n";

        file.close();
    }


    // ========================================================
    // DELETE CUSTOMER
    // ========================================================
    void deleteCustomer(string room) {

        ifstream file(filename);
        ofstream temp("temp.txt");

        Customer c;
        bool found = false;

        while (getline(file, c.roomnumber, '|')) {

            getline(file, c.name, '|');
            getline(file, c.address, '|');
            getline(file, c.phonenumber, '|');
            getline(file, c.nationality, '|');
            getline(file, c.email, '|');
            getline(file, c.period, '|');
            getline(file, c.arrivaldate);

            if (c.roomnumber == room) {

                found = true;
            }
            else {

                temp << c.roomnumber << "|"
                     << c.name << "|"
                     << c.address << "|"
                     << c.phonenumber << "|"
                     << c.nationality << "|"
                     << c.email << "|"
                     << c.period << "|"
                     << c.arrivaldate << "\n";
            }
        }

        file.close();
        temp.close();

        // Replace old file with new file
        remove("customers.txt");
        rename("temp.txt", "customers.txt");


        if (found) {

            cout << "----------------------------\n";
            cout << "Customer deleted successfully!\n";
            cout << "----------------------------\n";

        }
        else {

            cout << "----------------------------\n";
            cout << "Customer not found!\n";
            cout << "----------------------------\n";
        }
    }


    // ========================================================
    // UPDATE CUSTOMER
    // ========================================================
    void updateCustomer(string room) {

        ifstream file(filename);
        ofstream temp("temp.txt");

        Customer c;
        bool found = false;

        while (getline(file, c.roomnumber, '|')) {

            getline(file, c.name, '|');
            getline(file, c.address, '|');
            getline(file, c.phonenumber, '|');
            getline(file, c.nationality, '|');
            getline(file, c.email, '|');
            getline(file, c.period, '|');
            getline(file, c.arrivaldate);

            if (c.roomnumber == room) {

                found = true;

                cout << "Current details:\n";

                printHeader();

                printCustomer(c);

                cout << "\n";

                cout << "Enter new details:\n";

                cout << "Enter Full Name: ";
                getline(cin, c.name);

                cout << "Enter Address: ";
                getline(cin, c.address);

                cout << "Enter Phone Number: ";
                getline(cin, c.phonenumber);

                cout << "Enter Nationality: ";
                getline(cin, c.nationality);

                cout << "Enter Email: ";
                getline(cin, c.email);

                cout << "Enter Period (days): ";
                getline(cin, c.period);

                cout << "Enter Arrival Date (dd-mm-yyyy): ";
                getline(cin, c.arrivaldate);
            }

            // Write old or updated data to temporary file
            temp << c.roomnumber << "|"
                 << c.name << "|"
                 << c.address << "|"
                 << c.phonenumber << "|"
                 << c.nationality << "|"
                 << c.email << "|"
                 << c.period << "|"
                 << c.arrivaldate << "\n";
        }

        file.close();
        temp.close();

        remove("customers.txt");
        rename("temp.txt", "customers.txt");


        if (found) {

            cout << "Customer details updated successfully!\n";

        }
        else {

            cout << "----------------------------\n";
            cout << "Customer not found!\n";
            cout << "----------------------------\n";
        }
    }
};


// ============================================================
// LOGIN FUNCTION
// ============================================================
bool login(string &role) {

    const string correctUsername = "Admin";
    const string correctPassword = "admin123";

    string username;
    string password;

    const int maxAttempts = 3;


    cout << "\n============================\n";
    cout << "       HOTEL LOGIN\n";
    cout << "============================\n";


    for (int attempt = 1; attempt <= maxAttempts; attempt++) {

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);


        if (username == correctUsername &&
            password == correctPassword) {

            role = "admin";

            cout << "\n----------------------------\n";
            cout << "Login successful!\n";
            cout << "Welcome, " << username << "!\n";
            cout << "----------------------------\n";

            return true;
        }


        cout << "\nInvalid username or password!\n";

        cout << "Attempts remaining: "
             << maxAttempts - attempt << "\n\n";
    }


    cout << "Too many failed attempts.\n";
    cout << "Program terminated for security.\n";

    return false;
}


// ============================================================
// MAIN FUNCTION
// ============================================================
int main() {

    // Constructor is automatically called here
    HotelManager hotel;

    string role;


    if (!login(role)) {
        return 1;
    }


    while (true) {

        cout << "\n============================\n";
        cout << "    Hotel Management System\n";
        cout << "============================\n";

        cout << "1. Add Customer\n";
        cout << "2. List Customers\n";
        cout << "3. Search Customer\n";
        cout << "4. Delete Customer\n";
        cout << "5. Update Customer\n";
        cout << "6. Exit\n";

        cout << "----------------------------\n";


        cout << "Enter your choice: ";

        int choice;

        if (!(cin >> choice)) {

            cin.clear();

            choice = -1;
        }

        cin.ignore(1000, '\n');


        string roomInput;


        switch (choice) {

            case 1:

                hotel.addCustomer();

                break;


            case 2:

                hotel.displayCustomers();

                break;


            case 3:

                cout << "Enter Room Number to search: ";

                getline(cin, roomInput);

                hotel.searchCustomer(roomInput);

                break;

            case 4:

                // Display all customers before asking for room number
                hotel.displayCustomers();

                cout << "\nEnter Room Number to delete: ";

                getline(cin, roomInput);

                hotel.deleteCustomer(roomInput);

                break;


            case 5:
                // Display all customers before asking for room number
                hotel.displayCustomers();
                cout << "Enter Room Number to update: ";

                getline(cin, roomInput);

                hotel.updateCustomer(roomInput);

                break;


            case 6:

                cout << "\nExiting...\n";

                return 0;


            default:

                cout << "Invalid choice! Please try again.\n";
        }
        //asks whether to return to main menu or exit program
        cout << "Return to Main Menu? (y/n): ";

        string cont;

        getline(cin, cont);


        if (cont == "n" || cont == "N") {

            cout << "Exiting...\n";

            break;
        }
    }


    return 0;
}
