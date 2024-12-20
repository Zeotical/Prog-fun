// *********************************************************
// Program: YOUR_FILENAME.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class:
// Tutorial Class:
// Trimester: 2430
// Member_1: ID | NAME | EMAIL | PHONE
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: ID | NAME | EMAIL | PHONE
// *********************************************************
// Task Distribution
// Member_1:
// Member_2:
// Member_3:
// Member_4:
// *********************************************************

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct details {
    string customer_id;
    string customer_name;
    string customer_city;
    string customer_state;
    string customer_country;
    string customer_phone;
    string customer_email;
};

int main() {
    int customers;

    cout << "Enter the number of customers: ";
    cin >> customers;

    vector<details> people(customers);

    for (int i = 0; i < customers; ++i) {
        cout << "\nEnter details for customer " << i + 1 << ":" << endl;

        cout << "  ID: ";
        cin >> people[i].customer_id;

        cout << "  Name: ";
        cin >> people[i].customer_name;

        cout << "  City: ";
        cin >> people[i].customer_city;

        cout << "  State: ";
        cin >> people[i].customer_state;

        cout << "  Country: ";
        cin >> people[i].customer_country;

        cout << "  Phone number: ";
        cin >> people[i].customer_phone;

        cout << "  Email: ";
        cin >> people[i].customer_email;
    }

    // Print the table header
    cout << setw(20) << left << "ID"
         << setw(20) << left << "Name"
         << setw(10) << left << "City"
         << setw(20) << left << "State"
         << setw(20) << left << "Country"
         << setw(20) << left << "Phone number"
         << setw(20) << left << "Email" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    // Print the table data
    for (const details& person : people) {
        cout << setw(20) << left << person.customer_id << setw(20) << left << person.customer_name << setw(20) << left << person.customer_city << setw(20) << left << person.customer_state << setw(20) << left << person.customer_country << setw(20) << left << person.customer_phone << setw(20) << left << person.customer_email << endl;
    }

    return 0;
}
