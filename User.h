#pragma once

#include <string>
#include "UserState.h"

using namespace std;

class User {
protected:
    string username;
    string password;
    UserState* state;

public:
    User(const string& username, const string& password)
        : username(username), password(password), state(nullptr) {}

    void showMenu() {
        state->showMenu();
    }

    virtual Customer* getCustomer() {
        return nullptr;
    }

    virtual string getCustomerName() {
        return "";
    }

    virtual string getType() const = 0;
    virtual ~User() {}

    void setState(UserState* newState) {
        state = newState;
    }

    virtual void viewOrders() {
        state->viewOrders();
    }

    virtual void addBook(const string& title, const string& genre, string year, const string& publisher, double price, string stock, const vector<string>& authors) {}
    virtual void deleteBook(string bookId) {}

    virtual ~User() {
        delete state;
    }
};
