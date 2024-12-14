#ifndef NORMALUSER_H
#define NORMALUSER_H

#include <iostream>
#include "NormalUserState.h"
#include "User.h"
#include "Customer.h"

using namespace std;

class NormalUser : public User {
public:
    NormalUser(const string& username, const string& password, Customer* customer);
    NormalUser(const string& username, const string& password);
    Customer* getCustomer() override;
    string getType() const override;
    string getCustomerName() override;
    ~NormalUser() override;
};

#endif // NORMALUSER_H
