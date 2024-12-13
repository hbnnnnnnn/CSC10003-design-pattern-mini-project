#pragma once

#include <iostream>
#include "User.h"
#include "NormalUserState.h"
#include "Customer.h"

using namespace std;

class NormalUser : public User {
    Customer* customer;
public:
    NormalUser(const string& username, const string& password, Customer* customer) : User(username, password), customer(customer) {
        state = new NormalUserState();
    }
    NormalUser(const string& username, const string& password) : User(username, password), customer(nullptr) {
        state = new NormalUserState();
    }
    string getType() const override {
        return "customer";
    }
    Customer* getCustomer() {
        return customer;
    }
    string getCustomerName() {
        return customer->getName();
    }
    ~NormalUser() override {
        delete state;
        delete customer;
    }
};