#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "Book.h"
#include "Customer.h"
#include "Author.h"
#include "Order.h"
#include "User.h"
#include "AdminUser.h"
#include "NormalUser.h"
#include "BookSpecification.h"

using namespace std;

class ManageSys {
    friend class AdminState;
    vector<Book*> books;
    vector<Customer*> customers;
    vector<Author*> authors;
    vector<Order*> orders;
    User* currentUser;
    static ManageSys* instance;
    unordered_map<string, string> adminCredentials;
    unordered_map<string, string> normalUserCredentials;
    ManageSys() : currentUser(nullptr) {
        adminCredentials["admin1"] = "12345678";
        adminCredentials["admin2"] = "27072005";

        normalUserCredentials["user1"] = "21032005";
        normalUserCredentials["user2"] = "08032005";
    }
public:
    static ManageSys* getInstance() {
        if (!instance) {
            instance = new ManageSys();
        }
        return instance;
    }

    static void destroyInstance() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }

    bool login(const string& username, const string& password, const string& userType);
    void logout();
    User* getCurrentUser() { return currentUser; }

    // Book management
    void addBook(Book* book);
    Book* getBookById(string bookId);
    void deleteBook(string bookId);
    void addBook(const string& title, const string& genre, int year, const string& publisher, double price, int stock, const vector<string>& authors);
    void editBook(string bookId, double price);
    void editBook(string bookId, int stock);

    // Author management
    void addAuthor(Author* author);
    Author* getAuthorById(string authorId);
    void deleteAuthor(string authorId);
    void addAuthor(const string& name);
    void editAuthor(string authorId, const string& name);

    // Order management
    Order* getOrderById(string orderId);
    void viewOrders();
    void editOrder(string orderId, OrderStatus status);
    void cancelOrder(string orderId);

    // Reporting
    void reportRevenue(const string& period);
    void reportBooksSold(const string& period);
    void reportCustomerCount(const string& period);

    // Importing data
    void importBooksFromFile(const string& filename);
    void importAuthorsFromFile(const string& filename);
    void importOrdersFromFile(const string& filename);

    vector<Book*> searchBooks(BookSpecification* spec);
    void printBooks(vector<Book*> books);
    ~ManageSys();
};
