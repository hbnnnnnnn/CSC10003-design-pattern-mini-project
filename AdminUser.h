#pragma once

#include <iostream>
#include "User.h"

using namespace std;

class AdminState;
class ManageSys;
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
