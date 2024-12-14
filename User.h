#ifndef USER_H
#define USER_H

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

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    void setPassword(const string& newPassword) {
        password = newPassword;
    }

    virtual string getType() const = 0;

    void setState(UserState* newState) {
        state = newState;
    }

    virtual ~User() {
        if (state) {
            delete state; // Delete the state only if it's not nullptr
            state = nullptr; // Prevent accidental double deletion
        }
    }

};

#endif // USER_H
