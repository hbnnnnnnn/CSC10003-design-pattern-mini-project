#include "Customer.h"
#include "Order.h"

void Customer::display() {
    cout << "Customer Name: " << name << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Shipping Address: " << shippingAddress << endl;
}

Customer::Customer(const Customer& customer) {
    id = customer.id;
    name = customer.name;
    phoneNumber = customer.phoneNumber;
    email = customer.email;
    shippingAddress = customer.shippingAddress;
    for (const auto& order : customer.orderHistory) {
        orderHistory.push_back(order->clone());
    }
}
CustomerMemento* Customer::save() const {
    return new CustomerMemento(name, phoneNumber, email, shippingAddress);
}
void Customer::restore(CustomerMemento* memento) {
    name = memento->getName();
    phoneNumber = memento->getPhoneNumber();
    email = memento->getEmail();
    shippingAddress = memento->getShippingAddress();
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

const vector<Order*>& Customer::getOrderHistory() const {
    return orderHistory;
}

Customer::~Customer() {
for(auto& order : orderHistory) {
    delete order;
}
}