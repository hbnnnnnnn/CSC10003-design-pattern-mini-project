#pragma once
#include "Command.h"
#include "Order.h"
#include <iostream>
#include <iomanip>

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
