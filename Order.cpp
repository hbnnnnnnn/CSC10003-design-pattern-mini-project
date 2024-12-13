#include "Order.h"
#include <iomanip>
#include <iostream>
#include "OrderUtils.h"

Order::Order(const Order& order) {
    orderID = order.orderID;
    orderDate = order.orderDate;
    totalAmount = order.totalAmount;
    status = order.status;
    for (const auto& product : order.productList) {
        productList.push_back(make_pair(new Book(*product.first), product.second));
    }
    customer = new Customer(*order.customer);
    paymentStrategy = order.paymentStrategy ? order.paymentStrategy->clone() : nullptr;
}

Order* Order::clone() const {
    return new Order(*this);
}

void Order::display() {
    cout << "\nOrder ID: " << orderID << endl;
    cout << "Order Date: " << orderDate << endl;
    cout << "Total Amount: " << totalAmount << endl;
    cout << "Status: " << getStatusAsString(status.back()) << endl;
    cout << "Customer: " << customer->getName() << endl;

    // Display products
    cout << "\nProducts in Order:" << endl;
    cout << "| Book ID   | Title                | Quantity | Price  |" << endl;
    cout << "|-----------|----------------------|----------|--------|" << endl;
    for (const auto& product : productList) {
        cout << "| " << setw(10) << product.first->getId()
             << " | " << setw(20) << product.first->getName()
             << " | " << setw(8) << product.second
             << " | " << setw(6) << fixed << setprecision(2) << product.first->getPrice()
             << " |" << endl;
    }
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



void Order::displaySummary() {
    cout << "| " << setw(7) << orderID
         << " | " << setw(10) << orderDate
         << " | " << setw(10) << fixed << setprecision(2) << totalAmount
         << " | " << setw(10) << getStatusAsString(status.back())
         << " |" << endl;
}

Order::~Order() {
    for (auto& product : productList) {
        delete product.first;
    }
    if (paymentStrategy) {
        delete paymentStrategy;
    }
}
