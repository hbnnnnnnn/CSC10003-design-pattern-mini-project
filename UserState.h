#pragma once

#include <string>
#include <vector>
#include "Order.h"

using namespace std;
class User;

class UserState {
public:
    virtual ~UserState() {}
    virtual void showMenu() = 0;
};
