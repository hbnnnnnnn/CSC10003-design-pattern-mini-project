#ifndef USERSTATE_H
#define USERSTATE_H

#include <string>
#include <vector>
#include "Order.h"

using namespace std;

class UserState {
public:
    virtual ~UserState() {}
    virtual Customer* getCustomer() {
        return nullptr;
    }

    virtual string getCustomerName() {
        return "";
    }
    virtual void showMenu() = 0;
};

#endif // USERSTATE_H
