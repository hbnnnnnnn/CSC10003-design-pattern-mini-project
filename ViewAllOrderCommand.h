#pragma once
#include "Command.h"
#include "Order.h"
#include <iostream>
#include <iomanip>
#include "Command.h"

using namespace std;

//string getStatusAsString(OrderStatus status) {
//    switch (status) {
//        case OrderStatus::Placed: return "Placed";
//        case OrderStatus::Confirmed: return "Confirmed";
//        case OrderStatus::Paid: return "Paid";
//        case OrderStatus::Shipping: return "Shipping";
//        case OrderStatus::COD: return "COD";
//        case OrderStatus::Pending: return "Pending";
//        case OrderStatus::Delivered: return "Delivered";
//        case OrderStatus::Cancelled: return "Cancelled";
//        default: return "Unknown";
//    }
//}

class ViewAllOrdersCommand : public Command {
private:
    Customer* customer;

public:
    ViewAllOrdersCommand(Customer* customer) : customer(customer) {}

    void execute() override {
        const auto& orders = customer->getOrderHistory();
        if (orders.empty()) {
            cout << "No orders found." << endl;
            return;
        }

        cout << "\n> Your Orders:" << endl;
        cout << "| Order ID | Order Date  | Total Amount | Status      |" << endl;
        cout << "|----------|-------------|--------------|-------------|" << endl;
        for (const auto& order : orders) {
            cout << "| " << setw(10) << order->getOrderID()
                 << " | " << setw(12) << order->getOrderDate()
                 << " | " << setw(12) << fixed << setprecision(2) << order->getTotalAmount()
                 << " | " << setw(11) << getStatusAsString(order->getStatus().back())
                 << " |" << endl;
        }
    }
    void undo() override {}
};
