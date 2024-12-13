#include "ManageSys.h"
#include "CommandInvoker.h"
#include "AddToCartCommand.h"
#include "Command.h"
#include "ConfirmationCommand.h"
#include "CheckOutCommand.h"
#include "CreditCard.h"
#include "BankTransfer.h"
#include "EWallet.h"
#include "COD.h"
#include "PaymentStrategy.h"

void printHelp() {
    cout << "Available Commands:" << endl;
    int i = 1;
    cout << i++ << ". Login." << endl;
    cout << i++ << ". Sign up." << endl;
    cout << i++ << ". System - System management." << endl;
    cout << i++ << ". Search - Search for books." << endl;
    cout << i++ << ". View <BookID> - View detail of a book <BookID>." << endl;
    cout << i++ << ". Add <BookID, amount> - Add <amount> of <BookID> to cart." << endl;
    cout << i++ << ". Confirmation - review order information and confirm." << endl;
    cout << i++ << ". Check out - Select a payment method and complete the checkout process." << endl;
    cout << i++ << ". Account - Account management." << endl;
    cout << i++ << ". Order - Order management." << endl;
    cout << i++ << ". Help - Show this help message." << endl;
    cout << i++ << ". Exit - Exit the program." << endl;
    
}

ManageSys* ManageSys::instance = nullptr;
int main() {
    ManageSys* manager = ManageSys::getInstance();
    string command;
    static vector<Book*> cart;
    CommandInvoker invoker;
    Order* lastOrder = nullptr;

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
                size_t pos = command.find(",");
                if (pos != string::npos) {
                    string bookId = command.substr(4, pos - 4);
                    int amount = stoi(command.substr(pos + 1));
                    Command* addToCart = new AddToCartCommand(manager, bookId, amount, cart);
                    invoker.executeCommand(addToCart);
                } else {
                    cout << "Invalid command format. Use: Add <BookID, amount>" << endl;
                }
            }
        }

        else if (command.rfind("Confirmation", 0) == 0) {
            if (manager->getCurrentUser() == nullptr) {
                cout << "You must log in first." << endl;
            } else if (manager->getCurrentUser()->getType() == "customer") {
                Command* confirmation = new ConfirmationCommand(manager, cart);
                invoker.executeCommand(confirmation);
                lastOrder = confirmation->getLastOrder();
            }
        }

        

        else if (command.rfind("Check out", 0) == 0) {
            if (manager->getCurrentUser() == nullptr) {
                cout << "You must log in first." << endl;
            } else if (manager->getCurrentUser()->getType() == "customer") {
                cout << "Select a payment method:" << endl;
                cout << "> 1. Credit Card" << endl;
                cout << "> 2. Bank Transfer" << endl;
                cout << "> 3. EWallet" << endl;
                cout << "> 4. COD"  << endl;
                cout << "> Enter your choice (1-4): ";
                int choice;
                cin >> choice;
                PaymentStrategy* paymentMethod = nullptr;
                switch(choice) {
                    case 1:
                        paymentMethod = new CreditCard();
                        break;
                    case 2:
                        paymentMethod = new BankTransfer();
                        break;
                    case 3:
                        paymentMethod = new EWallet("Momo");
                        break;
                    case 4:
                        paymentMethod = new COD();
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                if(paymentMethod != nullptr) {
                    paymentMethod->input();
                    Command* checkOut = new CheckOutCommand(lastOrder, paymentMethod);
                    invoker.executeCommand(checkOut);
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
