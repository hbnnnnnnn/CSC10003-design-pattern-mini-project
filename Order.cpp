#include "Order.h"

void Order::display() {
    cout << "Order ID: " << orderID << endl;
    cout << "Order Date: " << orderDate << endl;
    cout << "Total Amount: " << totalAmount << endl;
    cout << "Status: ";
    for (const auto& stat : status) {
        switch (stat) {
            case OrderStatus::Placed:
                cout << "Placed ";
                break;
            case OrderStatus::Confirmed:
                cout << "Confirmed ";
                break;
            case OrderStatus::Paid:
                cout << "Paid ";
                break;
            case OrderStatus::Shipping:
                cout << "Shipping ";
                break;
            case OrderStatus::COD:
                cout << "COD ";
                break;
            case OrderStatus::Pending:
                cout << "Pending ";
                break;
            case OrderStatus::Delivered:
                cout << "Delivered ";
                break;
            case OrderStatus::Cancelled:
                cout << "Cancelled ";
                break;
        }
    }
    cout << "Products: " << endl;
    for (auto book : productList) {
        cout << book->getName() << endl;
    }
    cout << "Customer: " << customer->getName() << endl;
}

void Order::displayStatus() {
    cout << "Status: ";
    for (const auto& stat : status) {
        switch (stat) {
            case OrderStatus::Placed:
                cout << "Placed ";
                break;
            case OrderStatus::Confirmed:
                cout << "Confirmed ";
                break;
            case OrderStatus::Paid:
                cout << "Paid ";
                break;
            case OrderStatus::Shipping:
                cout << "Shipping ";
                break;
            case OrderStatus::COD:
                cout << "COD ";
                break;
            case OrderStatus::Pending:
                cout << "Pending ";
                break;
            case OrderStatus::Delivered:
                cout << "Delivered ";
                break;
            case OrderStatus::Cancelled:
                cout << "Cancelled ";
                break;
        }
    }
    cout << endl;
}