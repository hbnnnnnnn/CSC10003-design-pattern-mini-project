#pragma once

#include <iostream>
#include "NormalUserState.h"
#include "User.h"
#include "Customer.h"

using namespace std;

class NormalUser : public User {
public:
    NormalUser(const string& username, const string& password, Customer* customer) : User(username, password) {
        state = new NormalUserState(customer);
    }
    NormalUser(const string& username, const string& password) : User(username, password) {
        state = new NormalUserState;
    }
    virtual Customer* getCustomer() {
        return state->getCustomer();
    }

    virtual string getCustomerName() {
        return state->getCustomerName();
    }
    virtual string getType() const override {
        return "customer";
    }
    ~NormalUser() override {
        delete state;
    }
};
