#include "AdminState.h"
#include "Book.h"
#include "Author.h"
#include "Order.h"
#include <iostream>
#include <unordered_map>

using namespace std;

void AdminState::showMenu() {
    while (true) {
        cout << "> Management Categories:" << endl;
        cout << "> 1.  Book Management" << endl;
        cout << "> 2.  Author Management" << endl;
        cout << "> 3.  Order Management" << endl;
        cout << "> 4.  Report Management" << endl;
        cout << "> 5.  Import Management" << endl;
        cout << "> 6.  Quit" << endl;
        cout << "> Enter your choice (1-6): ";

        int choice;
        cin >> choice;

        string title, genre, publisher, bookId, name, authorId, newName, orderId, period, filename;
        int year;
        int stock;
        int newStock;
        float price, newPrice;
        int authorCount, status;
        vector<string> authors;

        switch (choice) {
            case 1: {
                cout << "> Book Management Commands:" << endl;
                cout << "> 1.  Add Book" << endl;
                cout << "> 2.  Edit Book Price" << endl;
                cout << "> 3.  Edit Book Stock" << endl;
                cout << "> 4.  Delete Book" << endl;
                cout << "> Enter your choice (1-4): ";
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "Enter book title: ";
                        cin.ignore();
                        getline(cin, title);
                        cout << "Enter book genre: ";
                        getline(cin, genre);
                        cout << "Enter book year: ";
                        cin >> year;
                        cin.ignore();
                        cout << "Enter book publisher: ";
                        getline(cin, publisher);
                        cout << "Enter book price: ";
                        cin >> price;
                        cout << "Enter book stock: ";
                        cin >> stock;
                        cin.ignore();
                        cout << "Enter author count: ";
                        cin >> authorCount;
                        cin.ignore();
                        for (int i = 0; i < authorCount; i++) {
                            cout << "Enter author name: ";
                            string author;
                            getline(cin, author);
                            authors.push_back(author);
                        }
                        addBook(title, genre, year, publisher, price, stock, authors);
                        break;
                    case 2:
                        cout << "Enter book ID: ";
                        cin >> bookId;
                        cout << "Enter new price: ";
                        cin >> newPrice;
                        editBook(bookId, newPrice);
                        break;
                    case 3:
                        cout << "Enter book ID: ";
                        cin >> bookId;
                        cout << "Enter new stock: ";
                        cin >> newStock;
                        editBook(bookId, newStock);
                        break;
                    case 4:
                        cout << "Enter book ID: ";
                        cin >> bookId;
                        deleteBook(bookId);
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                break;
            }
            case 2: {
                cout << "> Author Management Commands:" << endl;
                cout << "> 1.  Add Author" << endl;
                cout << "> 2.  Edit Author" << endl;
                cout << "> 3.  Delete Author" << endl;
                cout << "> Enter your choice (1-3): ";
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "Enter author name: ";
                        cin.ignore();
                        getline(cin, name);
                        addAuthor(name);
                        break;
                    case 2:
                        cout << "Enter author ID: ";
                        cin >> authorId;
                        cout << "Enter new name: ";
                        cin.ignore();
                        getline(cin, newName);
                        editAuthor(authorId, newName);
                        break;
                    case 3:
                        cout << "Enter author ID: ";
                        cin >> authorId;
                        deleteAuthor(authorId);
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                break;
            }
            case 3: {
                cout << "> Order Management Commands:" << endl;
                cout << "> 1.  View Orders" << endl;
                cout << "> 2.  Edit Order" << endl;
                cout << "> 3.  Cancel Order" << endl;
                cout << "> Enter your choice (1-3): ";
                cin >> choice;
                switch (choice) {
                    case 1:
                        viewOrders();
                        break;
                    case 2:
                        cout << "Enter order ID: ";
                        cin >> orderId;
                        cout << "Enter new status (0: Pending, 1: Shipped, 2: Delivered): ";
                        cin >> status;
                        editOrder(orderId, static_cast<OrderStatus>(status));
                        break;
                    case 3:
                        cout << "Enter order ID: ";
                        cin >> orderId;
                        cancelOrder(orderId);
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                break;
            }
            case 4: {
                cout << "> Report Management Commands:" << endl;
                cout << "> 1.  Report Revenue" << endl;
                cout << "> 2.  Report Books Sold" << endl;
                cout << "> 3.  Report Customer Count" << endl;
                cout << "> Enter your choice (1-3): ";
                cin >> choice;
                cout << "Enter period (e.g., 2021, 2021-01, 2021-01-01): ";
                cin.ignore();
                getline(cin, period);
                switch (choice) {
                    case 1:
                        reportRevenue(period);
                        break;
                    case 2:
                        reportBooksSold(period);
                        break;
                    case 3:
                        reportCustomerCount(period);
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                break;
            }
            case 5: {
                cout << "> Import Management Commands:" << endl;
                cout << "> 1.  Import Books From File" << endl;
                cout << "> 2.  Import Authors From File" << endl;
                cout << "> 3.  Import Orders From File" << endl;
                cout << "> Enter your choice (1-3): ";
                cin >> choice;
                cout << "Enter filename: ";
                cin.ignore();
                getline(cin, filename);
                switch (choice) {
                    case 1:
                        importBooksFromFile(filename);
                        break;
                    case 2:
                        importAuthorsFromFile(filename);
                        break;
                    case 3:
                        importOrdersFromFile(filename);
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
                break;
            }
            case 6:
                cout << "Quitting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void AdminState::addBook(const string& title, const string& genre, int year, const string& publisher, double price, int stock, const vector<string>& authors) {
    manageSys->addBook(title, genre, year, publisher, price, stock, authors);
}
void AdminState::editBook(string bookId, double price) {
    manageSys->editBook(bookId, price);
}
void AdminState::editBook(string bookId, int stock){
    manageSys->editBook(bookId, stock);
}
void AdminState::deleteBook(string bookId) {
    manageSys->deleteBook(bookId);
}

void AdminState::addAuthor(const string& name) {
    manageSys->addAuthor(name);
}
void AdminState::editAuthor(string authorId, const string& name) {
    manageSys->editAuthor(authorId, name);
}
void AdminState::deleteAuthor(string authorId) {
    manageSys->deleteAuthor(authorId);
}

void AdminState::viewOrders() {
    manageSys->viewOrders();
}
void AdminState::editOrder(string orderId, OrderStatus status) {
    manageSys->editOrder(orderId, status);
}
void AdminState::cancelOrder(string orderId) {
    manageSys->cancelOrder(orderId);
}

void AdminState::reportRevenue(const string& period) {
    manageSys->reportRevenue(period);
}
void AdminState::reportBooksSold(const string& period) {
    manageSys->reportBooksSold(period);
}
void AdminState::reportCustomerCount(const string& period) {
    manageSys->reportCustomerCount(period);
}

void AdminState::importBooksFromFile(const string& filename) {
    manageSys->importBooksFromFile(filename);
}
void AdminState::importAuthorsFromFile(const string& filename) {
    manageSys->importAuthorsFromFile(filename);
}
void AdminState::importOrdersFromFile(const string& filename) {
    manageSys->importOrdersFromFile(filename);
}

