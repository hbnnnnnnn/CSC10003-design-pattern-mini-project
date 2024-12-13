#include "Order.h"
#include <iomanip>
#include <iostream>

void Order::display() {
    // Define column widths
    const int idWidth = 10;
    const int titleWidth = 30;
    const int quantityWidth = 10;
    const int priceWidth = 10;
    const int totalWidth = 12;

    // Print header
    cout << "> Gio hang cua ban:" << endl;
    cout << "| " << left << setw(idWidth) << "Ma sach"
         << "| " << setw(titleWidth) << "Ten sach"
         << "| " << setw(quantityWidth) << "So luong"
         << "| " << setw(priceWidth) << "Don gia"
         << "| " << setw(totalWidth) << "Thanh tien"
         << "|" << endl;

    cout << "|-" << setfill('-') << setw(idWidth) << ""
         << "|-" << setw(titleWidth) << ""
         << "|-" << setw(quantityWidth) << ""
         << "|-" << setw(priceWidth) << ""
         << "|-" << setw(totalWidth) << ""
         << "-|" << setfill(' ') << endl;

    // Print product rows
    for (const auto& product : productList) {
        Book* book = product.first;
        int quantity = product.second;
        double totalPrice = book->getPrice() * quantity;

        cout << "| " << left << setw(idWidth) << book->getId()
             << "| " << setw(titleWidth) << book->getName()
             << "| " << setw(quantityWidth) << quantity
             << "| " << setw(priceWidth) << fixed << setprecision(0) << book->getPrice()
             << "| " << setw(totalWidth) << totalPrice
             << "|" << endl;
    }

    // Print total amount
    cout << "> Tong tien: " << fixed << setprecision(0) << totalAmount << endl;
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