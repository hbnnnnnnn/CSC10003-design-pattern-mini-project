#ifndef CUSTOMER_MEMENTO_H
#define CUSTOMER_MEMENTO_H

#include <string>

using namespace std;

class CustomerMemento {
private:
    string name;
    string phoneNumber;
    string email;
    string shippingAddress;

public:
    CustomerMemento(const string& name, const string& phone, const string& email, const string& address)
        : name(name), phoneNumber(phone), email(email), shippingAddress(address) {}

    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    string getEmail() const { return email; }
    string getShippingAddress() const { return shippingAddress; }
};

#endif // CUSTOMER_MEMENTO_H
