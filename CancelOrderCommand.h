#ifndef CANCEL_ORDER_COMMAND_H
#define CANCEL_ORDER_COMMAND_H

#include "Command.h"
#include "Order.h"
#include <iostream>

using namespace std;

class CancelOrderCommand : public Command {
private:
    Order* order;

public:
    CancelOrderCommand(Order* order) : order(order) {}

    void execute() override;
    void undo() override {}

};

#endif // CANCEL_ORDER_COMMAND_H
