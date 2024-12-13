#pragma once

#include <string>

using namespace std;

class Customer {
private:
    string id;
    string name;
    string phoneNumber;
    string email;
    string shippingAddress;

public:
    Customer(const string& id, const string& name, const string& phone, const string& email, const string& address)
        : id(id), name(name), phoneNumber(phone), email(email), shippingAddress(address) {}

    string getid() const { return id; }
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    string getEmail() const { return email; }
    string getShippingAddress() const { return shippingAddress; }

    void setName(const string& newName) { name = newName; }
    void setPhoneNumber(const string& newPhoneNumber) { phoneNumber = newPhoneNumber; }
    void setEmail(const string& newEmail) { email = newEmail; }
    void setShippingAddress(const string& newAddress) { shippingAddress = newAddress; }
};;