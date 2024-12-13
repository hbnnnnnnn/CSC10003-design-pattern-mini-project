#pragma once

#include "UserState.h"

class NormalUserState : public UserState {
public:
    void showMenu() override;

    void addBook(const string& title, const string& genre, int year, const string& publisher, double price, int stock, const vector<string>& authors) override;
    void editBook(string bookId, double price) override;
    void editBook(string bookId, int stock) override;
    void deleteBook(string bookId) override;

    void addAuthor(const string& name) override;
    void editAuthor(string authorId, const string& name) override;
    void deleteAuthor(string authorId) override;

    void viewOrders() override;
    void editOrder(string orderId, OrderStatus status) override;
    void cancelOrder(string orderId) override;

    void reportRevenue(const string& period) override;
    void reportBooksSold(const string& period) override;
    void reportCustomerCount(const string& period) override;

    void importBooksFromFile(const string& filename) override;
    void importAuthorsFromFile(const string& filename) override;
    void importOrdersFromFile(const string& filename) override;
};
