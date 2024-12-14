#ifndef VIEWORDERDETAILSCOMMAND_H
#define VIEWORDERDETAILSCOMMAND_H

#include "ManageSys.h"
#include "Command.h"
#include "Order.h"
#include <iostream>

using namespace std;

class ViewOrderDetailsCommand : public Command {
private:
    Order* order;

public:
    ViewOrderDetailsCommand(Order* order) : order(order) {}

    void execute() override {
        if (order != nullptr) {
            order->display();
        } else {
            cout << "Order not found." << endl;
        }
    }
    void undo() override {}
};

#endif // VIEWORDERDETAILSCOMMAND_H
