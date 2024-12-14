#ifndef BANKTRANSFER_H
#define BANKTRANSFER_H

#include "PaymentStrategy.h"
#include <iostream>

using namespace std;

class BankTransfer : public PaymentStrategy {
public:
    BankTransfer() = default;
    BankTransfer(const BankTransfer& bankTransfer) = default;
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
    PaymentStrategy* clone() const override {
        return new BankTransfer(*this);
    }
};

#endif // BANKTRANSFER_H
