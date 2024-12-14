#ifndef VIEW_ALL_ORDER_COMMAND_H
#define VIEW_ALL_ORDER_COMMAND_H

#include "Command.h"
#include "Order.h"
#include <iostream>
#include <iomanip>

using namespace std;

class Customer;
class ViewAllOrdersCommand : public Command {
private:
    Customer* customer;

public:
    ViewAllOrdersCommand(Customer* customer) : customer(customer) {}

    void execute() override;
    void undo() override {}
};

#endif // VIEW_ALL_ORDER_COMMAND_H
