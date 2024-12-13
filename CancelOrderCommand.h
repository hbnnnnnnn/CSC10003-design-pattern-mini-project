#pragma once
#include "Command.h"
#include "Order.h"
#include <iostream>

using namespace std;

string getStatusAsString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Placed: return "Da dat";
        case OrderStatus::Confirmed: return "Da xac nhan";
        case OrderStatus::Paid: return "Da thanh toan";
        case OrderStatus::Shipping: return "Dang giao";
        case OrderStatus::COD: return "COD";
        case OrderStatus::Pending: return "Dang xu ly";
        case OrderStatus::Delivered: return "Da giao";
        case OrderStatus::Cancelled: return "Da huy";
        default: return "Unknown";
    }
}

class CancelOrderCommand : public Command {
private:
    Order* order;

public:
    CancelOrderCommand(Order* order) : order(order) {}

    void execute() override {
        if (order->getStatus().back() == OrderStatus::Placed ||
            order->getStatus().back() == OrderStatus::Confirmed) {
            order->setOrderStatus({OrderStatus::Cancelled});
            cout << "Order " << order->getOrderID() << " has been cancelled." << endl;
        } else {
            cout << "Order cannot be cancelled as it is in the '"
                 << getStatusAsString(order->getStatus().back()) << "' state." << endl;
        }
    }
    void undo() override {}

};
