#include "Customer.h"

 void Customer::display() {
        cout << "Customer Name: " << name << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Shipping Address: " << shippingAddress << endl;
 }

  void Customer::input() {
        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone Number: ";
        cin >> phoneNumber;
        cout << "Enter Shipping Address: ";
        cin.ignore();
        getline(cin, shippingAddress);
  }