#include "AdminState.h"
#include "Book.h"
#include "Author.h"
#include "Order.h"
#include <iostream>
#include <unordered_map>

using namespace std;

void AdminState::showMenu() {
    while (true) {
        cout << "\n> Admin Menu:" << endl;
        cout << "> Book management" << endl;
        cout << "> Author management" << endl;
        cout << "> Order management" << endl;
        cout << "> Report management" << endl;
        cout << "> Import management" << endl;
        cout << "> Quit" << endl;
        cout << "Enter a command (e.g., 'Book management' or 'Quit'): ";
        
        string input;
        cin.ignore();
        getline(cin, input);

        if (input.rfind("Book management", 0) == 0) {
            bookManagementMenu();
        } else if (input.rfind("Author management", 0) == 0) {
            authorManagementMenu();
        } else if (input.rfind("Order management", 0) == 0) {
            orderManagementMenu();
        } else if (input.rfind("Report management", 0) == 0) {
            reportManagementMenu();
        } else if (input.rfind("Import management", 0) == 0) {
            importManagementMenu();
        } else if (input.rfind("Quit", 0) == 0) {
            cout << "Exiting admin menu..." << endl;
            break;
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
}

void AdminState::orderManagementMenu() {
    while (true) {
        cout << "\n> Order Management:" << endl;
        cout << "    > 1. View orders" << endl;
        cout << "    > 2. Edit order" << endl;
        cout << "    > 3. Cancel order" << endl;
        cout << "    > 4. Back" << endl;
        cout << "Enter your choice (1-4): ";
        
        int choice;
        cin >> choice;

        string orderId;
        int status;

        switch (choice) {
            case 1:
                manageSys->viewOrders();
                break;
            case 2:
                cout << "> Enter order ID: ";
                cin >> orderId;
                cout << "> Enter new status (0: Pending, 1: Shipped, 2: Delivered): ";
                cin >> status;
                manageSys->editOrder(orderId, static_cast<OrderStatus>(status));
                break;
            case 3:
                cout << "> Enter order ID: ";
                cin >> orderId;
                manageSys->cancelOrder(orderId);
                break;
            case 4:
                return; // Go back to the top-level menu
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void AdminState::bookManagementMenu() {
    while (true) {
        cout << "\n> Book Management:" << endl;
        cout << "    > 1. Add book" << endl;
        cout << "    > 2. Edit book price" << endl;
        cout << "    > 3. Edit book stock" << endl;
        cout << "    > 4. Delete book" << endl;
        cout << "    > 5. Back" << endl;
        cout << "Enter your choice (1-5): ";
        
        int choice;
        cin >> choice;

        string title, genre, publisher, bookId;
        int year, stock;
        double price;

        switch (choice) {
            case 1:
                cout << "> Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "> Enter book genre: ";
                getline(cin, genre);
                cout << "> Enter year of publication: ";
                cin >> year;
                cout << "> Enter publisher: ";
                cin.ignore();
                getline(cin, publisher);
                cout << "> Enter price: ";
                cin >> price;
                cout << "> Enter stock quantity: ";
                cin >> stock;
                manageSys->addBook(title, genre, year, publisher, price, stock, {});
                break;
            case 2:
                cout << "> Enter book ID: ";
                cin >> bookId;
                cout << "> Enter new price: ";
                cin >> price;
                manageSys->editBook(bookId, price);
                break;
            case 3:
                cout << "> Enter book ID: ";
                cin >> bookId;
                cout << "> Enter new stock: ";
                cin >> stock;
                manageSys->editBook(bookId, stock);
                break;
            case 4:
                cout << "> Enter book ID: ";
                cin >> bookId;
                manageSys->deleteBook(bookId);
                break;
            case 5:
                return; // Go back to the top-level menu
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void AdminState::reportManagementMenu() {
    while (true) {
        cout << "\n> Report Management:" << endl;
        cout << "    > 1. Report Revenue" << endl;
        cout << "    > 2. Report Books Sold" << endl;
        cout << "    > 3. Report Customer Count" << endl;
        cout << "    > 4. Back" << endl;
        cout << "Enter your choice (1-4): ";

        int choice;
        cin >> choice;

        string period;

        switch (choice) {
            case 1:
                cout << "> Enter period (e.g., '2023', '2023-01', '2023-01-15'): ";
                cin.ignore();
                getline(cin, period);
                manageSys->reportRevenue(period);
                break;
            case 2:
                cout << "> Enter period (e.g., '2023', '2023-01', '2023-01-15'): ";
                cin.ignore();
                getline(cin, period);
                manageSys->reportBooksSold(period);
                break;
            case 3:
                cout << "> Enter period (e.g., '2023', '2023-01', '2023-01-15'): ";
                cin.ignore();
                getline(cin, period);
                manageSys->reportCustomerCount(period);
                break;
            case 4:
                return; // Go back to the top-level menu
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void AdminState::importManagementMenu() {
    while (true) {
        cout << "\n> Import Management:" << endl;
        cout << "    > 1. Import Books from File" << endl;
        cout << "    > 2. Import Authors from File" << endl;
        cout << "    > 3. Import Orders from File" << endl;
        cout << "    > 4. Back" << endl;
        cout << "Enter your choice (1-4): ";

        int choice;
        cin >> choice;

        string filename;

        switch (choice) {
            case 1:
                cout << "> Enter filename for books (e.g., 'books.csv'): ";
                cin.ignore();
                getline(cin, filename);
                manageSys->importBooksFromFile(filename);
                break;
            case 2:
                cout << "> Enter filename for authors (e.g., 'authors.csv'): ";
                cin.ignore();
                getline(cin, filename);
                manageSys->importAuthorsFromFile(filename);
                break;
            case 3:
                cout << "> Enter filename for orders (e.g., 'orders.csv'): ";
                cin.ignore();
                getline(cin, filename);
                manageSys->importOrdersFromFile(filename);
                break;
            case 4:
                return; // Go back to the top-level menu
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void AdminState::authorManagementMenu() {
    while (true) {
        cout << "\n> Author Management:" << endl;
        cout << "    > 1. Add author" << endl;
        cout << "    > 2. Edit author" << endl;
        cout << "    > 3. Delete author" << endl;
        cout << "    > 4. Back" << endl;
        cout << "Enter your choice (1-4): ";

        int choice;
        cin >> choice;

        string name, authorId, newName;

        switch (choice) {
            case 1:
                cout << "> Enter author name: ";
                cin.ignore();
                getline(cin, name);
                manageSys->addAuthor(name);
                break;
            case 2:
                cout << "> Enter author ID: ";
                cin >> authorId;
                cout << "> Enter new author name: ";
                cin.ignore();
                getline(cin, newName);
                manageSys->editAuthor(authorId, newName);
                break;
            case 3:
                cout << "> Enter author ID: ";
                cin >> authorId;
                manageSys->deleteAuthor(authorId);
                break;
            case 4:
                return; // Go back to the top-level menu
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

