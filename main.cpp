#include "ManageSys.h"
#include "AdminState.h"
#include "NormalUserState.h"
#include <iostream>
#include <string>

using namespace std;

void printHelp() {
    cout << "\nAvailable Commands:" << endl;
    cout << "1. Login - Log in as admin or customer." << endl;
    cout << "2. Sign up - Create a new admin or customer account." << endl;
    cout << "3. Exit - Exit the program." << endl;
}

int main() {
    ManageSys* manager = ManageSys::getInstance();
    string command;

    cout << "Welcome to the Bookstore Management System!" << endl;
    cout << "Type 'help' for a list of commands." << endl;

    while (true) {
        cout << "\n> ";
        getline(cin, command);

        if (command == "help") {
            printHelp();
        } else if (command == "Login") {
            cout << "1. Admin" << endl;
            cout << "2. Customer" << endl;
            cout << "Enter user type (1-2): ";
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice != 1 && choice != 2) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }

            string userType = (choice == 1) ? "admin" : "customer";
            string username, password;

            cout << "Enter username: ";
            getline(cin, username);

            cout << "Enter password: ";
            getline(cin, password);

            if (!manager->login(username, password, userType)) {
                cout << "Login failed. Please try again." << endl;
                continue;
            }

            // Delegate to the logged-in user's state
            User* currentUser = manager->getCurrentUser();
            if (userType == "admin") {
                AdminState adminState(manager);
                adminState.showMenu();
            } else if (userType == "customer") {
                NormalUserState normalUserState;
                normalUserState.showMenu();
            }

            // After the user logs out
            manager->logout();
        } 
        else if (command == "Sign up") {
            cout << "1. Admin" << endl;
            cout << "2. Customer" << endl;
            cout << "Enter user type (1-2): ";
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice != 1 && choice != 2) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }

            string userType = (choice == 1) ? "admin" : "customer";
            string username, password;

            cout << "Enter username: ";
            getline(cin, username);

            cout << "Enter password: ";
            getline(cin, password);

            if (!manager->signup(username, password, userType)) {
                cout << "Sign up failed. Username might already exist." << endl;
                continue;
            }

            cout << "Account created successfully. Please login to proceed." << endl;
        } 
        else if (command == "Exit") {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        } 
        else {
            cout << "Invalid command. Please try again." << endl;
        }
    }

    ManageSys::destroyInstance();
    return 0;
}
