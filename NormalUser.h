#pragma once

#include <iostream>
#include "User.h"
#include "NormalUserState.h"

using namespace std;

class NormalUser : public User {
public:
    NormalUser(const string& username, const string& password) : User(username, password) {
        state = new NormalUserState();
    }
    string getType() const override {
        return "normal";
    }
    ~NormalUser() {}
};