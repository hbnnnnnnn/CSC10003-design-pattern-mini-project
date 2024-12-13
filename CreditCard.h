#pragma once
#include "PaymentStrategy.h"
#include <iostream>

using namespace std;

class CreditCard : public PaymentStrategy {
private:
    string cardNumber;
    string expiryDate;
    string cvv;

public:
    CreditCard() = default;
    CreditCard(const CreditCard& creditCard) = default;
    CreditCard(const string& cardNumber, const string& expiryDate, const string& cvv)
        : cardNumber(cardNumber), expiryDate(expiryDate), cvv(cvv) {}

    void input() override {
        cout << "Enter card number: ";
        cin >> cardNumber;
        cout << "Enter expiry date: ";
        cin >> expiryDate;
        cout << "Enter CVV: ";
        cin >> cvv;
    }
    bool pay(float amount) override {
        cout << "Processing credit card payment..." << endl;
        cout << "Card Number: " << cardNumber << endl;
        cout << "Amount: $" << amount << " successfully paid via Credit Card." << endl;
        return true;
    }
    string getPaymentMethod() override {
        return "Credit Card";
    }
    PaymentStrategy* clone() const override {
        return new CreditCard(*this);
    }
};
