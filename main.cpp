#include "ManageSys.h"

void printHelp() {
    cout << "Available Commands:" << endl;
    cout << "1. Login" << endl;
    cout << "2. System - System management" << endl;
    cout << "3. Search - Search for books" << endl;
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
        else if (command.rfind("Search",0) == 0) {
            // Command: Search for books
            if (manager->getCurrentUser() == nullptr) {
                cout << "You must log in first." << endl;
            } else {
                cout << "> Enter search specification: ";
                cout << "> 1. Title" << endl;
                cout << "> 2. Genre" << endl;
                cout << "> 3. Author" << endl;
                cout << "> 4. Publisher" << endl;
                cout << "> 5. Price Range" << endl;
                cout << "> Enter your choice (1-5): ";
                int choice;
                cin >> choice;
                cin.ignore();
                BookSpecification* spec = nullptr;
                switch(choice) {
                    case 1: {
                        cout << "Enter book title: ";
                        string title;
                        getline(cin, title);
                        spec = new BookTitleBookSpecification(title);
                        break;
                    }
                    case 2: {
                        cout << "Enter book genre: ";
                        string genre;
                        getline(cin, genre);
                        spec = new BookGenreBookSpecification(genre);
                        break;
                    }
                    case 3: {
                        cout << "Enter author name: ";
                        string author;
                        getline(cin, author);
                        spec = new BookAuthorBookSpecification(author);
                        break;
                    }
                    case 4: {
                        cout << "Enter publisher name: ";
                        string publisher;
                        getline(cin, publisher);
                        spec = new BookPublisherBookSpecification(publisher);
                        break;
                    }
                    case 5: {
                        cout << "Enter minimum price: ";
                        double minPrice;
                        cin >> minPrice;
                        cout << "Enter maximum price: ";
                        double maxPrice;
                        cin >> maxPrice;
                        spec = new BookPriceRangeBookSpecification(minPrice, maxPrice);
                        break;
                    }
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                if (spec != nullptr) {
                    vector<Book*> books = manager->searchBooks(spec);
                    manager->printBooks(books);
                    delete spec;
                }
            }
        }
        else if (command.rfind("delete",0) == 0) {
            // Command: Delete a book by its ID
            if (manager->getCurrentUser() == nullptr) {
                cout << "You must log in first." << endl;
            } else if (manager->getCurrentUser()->getType() == "admin") {
                cout << "Enter book ID: ";
                string bookId;
                getline(cin, bookId);
                manager->deleteBook(bookId);
            } else {
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
