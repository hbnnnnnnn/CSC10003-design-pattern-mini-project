#pragma once
#include "PaymentStrategy.h"
#include <iostream>

using namespace std;

class COD : public PaymentStrategy {
public:
    COD() = default;
    void input() override {
        cout << "No input required for COD." << endl;
    }
    bool pay(float amount) override {
        cout << "Order confirmed for COD." << endl;
        cout << "Amount: $" << amount << " will be paid upon delivery." << endl;
        return false;
    }
    string getPaymentMethod() override {
        return "COD";
    }
};