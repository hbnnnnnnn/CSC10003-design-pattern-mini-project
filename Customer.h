#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include "CustomerMemento.h"
#include <vector>

using namespace std;

class Order;
class Customer {
private:
    string id;
    string name;
    string phoneNumber;
    string email;
    string shippingAddress;
    vector<Order*> orderHistory;

public:
    Customer() = default;
    Customer(const string& id, const string& name, const string& phone, const string& email, const string& address)
        : id(id), name(name), phoneNumber(phone), email(email), shippingAddress(address) {}
    Customer(const Customer& customer);
    CustomerMemento* save() const;

    void restore(CustomerMemento* memento);

    string getid() const { return id; }
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    string getEmail() const { return email; }
    string getShippingAddress() const { return shippingAddress; }
    const vector<Order*>& getOrderHistory() const;

    void setName(const string& newName) { name = newName; }
    void setPhoneNumber(const string& newPhoneNumber) { phoneNumber = newPhoneNumber; }
    void setEmail(const string& newEmail) { email = newEmail; }
    void setShippingAddress(const string& newAddress) { shippingAddress = newAddress; }

    void display();
    void input();  
    void addOrder(Order* order) { orderHistory.push_back(order); }
    Order* getOrderById(const string& orderId);
    ~Customer();
};

#endif // CUSTOMER_H