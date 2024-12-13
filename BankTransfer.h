#pragma once
#include "PaymentStrategy.h"
#include <iostream>

using namespace std;

class BankTransfer : public PaymentStrategy {
public:
    BankTransfer() = default;
    void input() override {
        cout << "No input required for COD." << endl;
    }
    bool pay(float amount) override {
        cout << "Processing bank transfer payment..." << endl;
        cout << "Bank Account: 123456789 - Bank XYZ" << endl;
        cout << "Amount: $" << amount << " successfully transferred via Bank Transfer." << endl;
        return true;
    }
    string getPaymentMethod() override {
        return "Bank Transfer";
    }
};
