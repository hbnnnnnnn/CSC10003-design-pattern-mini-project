#include "ManageSys.h"

void printHelp() {
    cout << "Available Commands:" << endl;
    cout << "1. Login" << endl;
    cout << "2. System Management" << endl;
    cout << "2. view - View all books" << endl;
    cout << "3. delete <id> - Delete a book by its ID" << endl;
    cout << "4. help - Show this help message" << endl;
    cout << "5. exit - Exit the program" << endl;
}

ManageSys* ManageSys::instance = nullptr;
int main() {
    ManageSys* manager = ManageSys::getInstance();
    string command;

    cout << "Welcome to the Bookstore Management System!" << endl;
    cout << "Type 'help' for a list of commands." << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command.rfind("Login", 0) == 0) {
            // Command: Log-in (admin/ normal)
            cout << "1. Admin" << endl;
            cout << "2. Normal" << endl;
            cout << "Enter user type (1-2): ";
            int choice;
            cin >> choice;
            cin.ignore();
            if (choice != 1 && choice != 2) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            string userType;
            if (choice == 1) {
                userType = "admin";
            } else {
                userType = "normal";
            }
            cout << "Enter username: ";
            string username;
            getline(cin, username);
            cout << "Enter password: ";
            string password;
            getline(cin, password);
            manager->login(username, password, userType);
        } else if (command.rfind("System", 0) == 0) {
            // Command: System Management
            if (manager->getCurrentUser() == nullptr) {
                cout << "You must log in first." << endl;
            } else if (manager->getCurrentUser()->getType() == "admin") {
                manager->getCurrentUser()->showMenu();
                continue;
            }
            else {
                cout << "You are not authorized to access this feature." << endl;
            }
        }
        else if (command.rfind("help",0) == 0){
            printHelp();
        }
        else if (command.rfind("exit",0) == 0) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid command. Type 'help' for a list of commands." << endl;
        }
    }

    return 0;
}
