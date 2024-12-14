#ifndef ADMINUSER_H
#define ADMINUSER_H

#include <iostream>
#include "User.h"

using namespace std;

class AdminUser : public User {
public:
    AdminUser(const string& username, const string& password);
    string getType() const override {
        return "admin";
    }
    ~AdminUser() override {
        delete state;
    }
};

#endif // ADMINUSER_H
