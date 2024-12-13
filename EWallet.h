#pragma once
#include "PaymentStrategy.h"
#include <iostream>

using namespace std;

class EWallet : public PaymentStrategy {
private:
    string walletName;

public:
    EWallet() = default;
    EWallet(const string& walletName) : walletName(walletName) {}

    void input() override {
        cout << "Enter " << walletName << " username: ";
        cin >> walletName;
    }

    bool pay(float amount) override {
        cout << "Processing e-wallet payment with " << walletName << "..." << endl;
        cout << "[Displaying QR Code]" << endl;
        cout << "Amount: " << amount << " successfully paid via " << walletName << "." << endl;
        return true;
    }
    string getPaymentMethod() override {
        return "E-Wallet";
    }
};
