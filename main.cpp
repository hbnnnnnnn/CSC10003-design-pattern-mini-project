#include "ManageSys.h"
#include "CommandInvoker.h"
#include "AddToCartCommand.h"
#include "Command.h"
#include "CheckOutCommand.h"

void printHelp() {
    cout << "Available Commands:" << endl;
    int i = 1;
    cout << i++ << ". Login" << endl;
    cout << i++ << ". Sign up" << endl;
    cout << i++ << ". System - System management" << endl;
    cout << i++ << ". Search - Search for books" << endl;
    cout << i++ << ". View <BookID> - View detail of a book <BookID>" << endl;
    cout << i++ << ". Add <BookID> - Add a book to cart" << endl;
    cout << i++ << ". Check out - order information" << endl;
    cout << i++ << ". help - Show this help message" << endl;
    cout << i++ << ". exit - Exit the program" << endl;
    
}

ManageSys* ManageSys::instance = nullptr;
int main() {
    ManageSys* manager = ManageSys::getInstance();
    string command;
    static vector<Book*> cart;
    CommandInvoker invoker;

    cout << "Welcome to the Bookstore Management System!" << endl;
    cout << "Type 'help' for a list of commands." << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command.rfind("Login", 0) == 0) {
            // Command: Log-in (admin/ normal)
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
            string userType;
            if (choice == 1) {
                userType = "admin";
            } else {
                userType = "customer";
            }
            cout << "Enter username: ";
            string username;
            getline(cin, username);
            cout << "Enter password: ";
            string password;
            getline(cin, password);
            manager->login(username, password, userType);
        } 
        else if (command.rfind("Sign up", 0) == 0) {
            // Command: Sign up (admin/ customer)
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
            string userType;
            if (choice == 1) {
                userType = "admin";
            } else {
                userType = "customer";
            }
            cout << "Enter username: ";
            string username;
            getline(cin, username);
            cout << "Enter password: ";
            string password;
            getline(cin, password);
            manager->signup(username, password, userType);
        }
        else if (command.rfind("System", 0) == 0) {
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
        else if (command.rfind("View",0) == 0) {
            // Command: View detail of a book by its ID
            if (manager->getCurrentUser() == nullptr) {
                cout << "You must log in first." << endl;
            } else {
                string bookId = command.substr(5);
                Book* book = manager->getBookById(bookId);
                if (book != nullptr) {
                    cout << "> Book Detail " << book->getId() << endl;
                    book->display();
                    delete book;
                } else {
                    cout << "Book not found." << endl;
                }
            }
        }
        else if (command.rfind("Add", 0) == 0) {
            if (manager->getCurrentUser() == nullptr) {
                cout << "You must log in first." << endl;
            } else if (manager->getCurrentUser()->getType() == "customer") {
                string bookId = command.substr(4);
                AddToCartCommand* addToCart = new AddToCartCommand(manager, bookId, cart);
                invoker.executeCommand(addToCart);
            }
        }

        else if (command.rfind("Check out", 0) == 0) {
            if (manager->getCurrentUser() == nullptr) {
                cout << "You must log in first." << endl;
            } else if (manager->getCurrentUser()->getType() == "customer") {
                CheckoutCommand* checkout = new CheckoutCommand(manager, cart);
                invoker.executeCommand(checkout);
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
