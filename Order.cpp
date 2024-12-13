#include "Order.h"

void Order::display() {
    cout << "Order ID: " << orderID << endl;
    cout << "Order Date: " << orderDate << endl;
    cout << "Total Amount: " << totalAmount << endl;
    cout << "Status: ";
    switch (status) {
        case OrderStatus::Placed:
            cout << "Placed" << endl;
            break;
        case OrderStatus::Confirmed:
            cout << "Confirmed" << endl;
            break;
        case OrderStatus::Paid:
            cout << "Paid" << endl;
            break;
        case OrderStatus::Shipping:
            cout << "Shipping" << endl;
            break;
        case OrderStatus::Delivered:
            cout << "Delivered" << endl;
            break;
        case OrderStatus::Cancelled:
            cout << "Cancelled" << endl;
            break;
    }
    cout << "Products: " << endl;
    for (auto book : productList) {
        cout << book->getName() << endl;
    }
    cout << "Customer: " << customer->getName() << endl;
}