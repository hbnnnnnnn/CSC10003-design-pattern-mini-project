#pragma once

#include <string>
#include <vector>
#include "Book.h"
#include "Customer.h"

using namespace std;

enum class OrderStatus {
    Placed,
    Confirmed,
    Paid,
    Shipping,
    Delivered,
    Cancelled
};

class Order {
private:
    string orderID;
    string orderDate;
    float totalAmount;
    OrderStatus status;
    vector<Book*> productList;
    Customer* customer;

public:
    Order(const string& id, const string& date, float amount, OrderStatus stat, const vector<Book*>& products, Customer* cust)
        : orderID(id), orderDate(date), totalAmount(amount), status(stat), productList(products), customer(cust) {}

    string getOrderID() const { return orderID; }
    string getOrderDate() const { return orderDate; }
    double getTotalAmount() const { return totalAmount; }
    OrderStatus getStatus() const { return status; }
    vector<Book*> getProductList() const { return productList; }
    Customer* getCustomer() const { return customer; }

    void setOrderID(const string& id) { orderID = id; }
    void setOrderStatus(OrderStatus stat) { status = stat; }
    void display();
};;