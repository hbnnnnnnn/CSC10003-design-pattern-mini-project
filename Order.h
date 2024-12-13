#pragma once

#include <string>
#include <vector>
#include "Book.h"
#include "Customer.h"
#include "PaymentStrategy.h"
#include <utility>

using namespace std;

enum class OrderStatus {
    Placed,
    Confirmed,
    Paid,
    Shipping,
    COD,
    Pending,
    Delivered,
    Cancelled
};

class Order {
private:
    string orderID;
    string orderDate;
    float totalAmount;
    vector<OrderStatus> status;
    vector<pair<Book*, int>> productList;
    Customer* customer;
    PaymentStrategy* paymentStrategy;

public:
    Order(const string& id, const string& date, float amount, vector<OrderStatus> stat, vector<pair<Book*, int>>& products, Customer* cust)
        : orderID(id), orderDate(date), totalAmount(amount), status(stat), productList(products), customer(cust), paymentStrategy(nullptr) {}
    string getOrderID() const { return orderID; }
    string getOrderDate() const { return orderDate; }
    double getTotalAmount() const { return totalAmount; }
    vector<OrderStatus> getStatus() const { return status; }
    vector<pair<Book*, int>> getProductList() const { return productList; }
    Customer* getCustomer() const { return customer; }

    void setOrderID(const string& id) { orderID = id; }
    void setOrderStatus(vector<OrderStatus> stat) { status = stat; }
    void setPaymentStrategy(PaymentStrategy* strategy) { paymentStrategy = strategy; }
    void display();
    void displayStatus();
};

