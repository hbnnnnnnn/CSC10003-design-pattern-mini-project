#pragma once
#include "PaymentStrategy.h"
#include <iostream>

using namespace std;

class EWallet : public PaymentStrategy {
private:
    string walletName;

public:
    EWallet() = default;
    EWallet(const EWallet& eWallet) : walletName(eWallet.walletName) {}
    EWallet(const string& walletName) : walletName(walletName) {}

    void input() override {
        cout << "> Choose an E-Wallet:" << endl; 
        cout << "> 1. Zalopay" << endl;
        cout << "> 2. Momo" << endl;
        cout << "> 3. ShopeePay" << endl;
        cout << "> Enter your choice (1-3): ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                walletName = "Zalopay";
                break;
            case 2:
                walletName = "Momo";
                break;
            case 3:
                walletName = "ShopeePay";
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
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
    PaymentStrategy* clone() const override {
        return new EWallet(*this);
    }
};

