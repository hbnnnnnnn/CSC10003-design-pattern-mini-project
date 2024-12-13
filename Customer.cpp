#include "Customer.h"
#include "Order.h"

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
        cout << "Enter Email: ";
        cin >> email;
  }

  Order* Customer::getOrderById(const string& orderId) {
        for(auto& order : orderHistory) {
            if(order->getOrderID() == orderId) {
                return order;
            }
        }
        return nullptr;
  }

  Customer::~Customer() {
    for(auto& order : orderHistory) {
        delete order;
    }
  }