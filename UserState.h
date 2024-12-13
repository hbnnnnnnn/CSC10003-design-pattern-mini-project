#pragma once

#include <string>
#include <vector>
#include "Order.h"

using namespace std;
class User;

class UserState {
public:
    virtual ~UserState() {}
    virtual void viewOrders() = 0;
    virtual void showMenu() = 0;

    virtual void addBook(const string& title, const string& genre, int year, const string& publisher, double price, int stock, const vector<string>& authors) {}
    virtual void deleteBook(string bookId) {}
    virtual void editBook(string bookId, double price) = 0;
    virtual void editBook(string bookId, int stock) = 0;

    virtual void addAuthor(const string& name) = 0;
    virtual void editAuthor(string authorId, const string& name) = 0;
    virtual void deleteAuthor(string authorId) = 0;

    virtual void editOrder(string orderId, OrderStatus status) = 0;
    virtual void cancelOrder(string orderId) = 0;

    virtual void reportRevenue(const string& period) = 0;
    virtual void reportBooksSold(const string& period) = 0;
    virtual void reportCustomerCount(const string& period) = 0;

    virtual void importBooksFromFile(const string& filename) = 0;
    virtual void importAuthorsFromFile(const string& filename) = 0;
    virtual void importOrdersFromFile(const string& filename) = 0;
};
