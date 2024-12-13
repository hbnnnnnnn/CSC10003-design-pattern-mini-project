#pragma once
#include "ManageSys.h"
#include "Command.h"
#include "PaymentStrategy.h"
#include "EWallet.h"
#include "BankTransfer.h"
#include "CreditCard.h"
#include "COD.h"

class CheckOutCommand : public Command {
private:
    ManageSys* manager;
    Order* order;
    PaymentStrategy* paymentMethod;

public:
    CheckOutCommand(Order* order, PaymentStrategy* paymentMethod)
        : order(order), paymentMethod(paymentMethod) {}

    void execute() override {

        if (manager->getCurrentUser() && manager->getCurrentUser()->getType() == "customer") {
            if(order->getProductList().empty()){
                cout << "Cart is empty." << endl;
                return;
            }

            cout << "Order " << order->getOrderID() << " details:" << endl;
            cout << "Order Date: " << order->getOrderDate() << endl;
            cout << "List of products: " << endl;
            order->display();
            cout << "Total: " << order->getTotalAmount() << endl;
            order->displayStatus();

            cout << "> Choose a payment method:" << endl;
            cout << "> 1. Credit Card" << endl;
            cout << "> 2. Bank Transfer" << endl;
            cout << "> 3. E-Wallet" << endl;
            cout << "> 4. COD" << endl;
            cout << "> Enter your choice (1-4): ";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1:
                    paymentMethod = new CreditCard();
                    break;
                case 2:
                    paymentMethod = new BankTransfer();
                    break;
                case 3:
                    paymentMethod = new EWallet();
                    break;
                case 4:
                    paymentMethod = new COD();
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }

            paymentMethod->input();
            bool paid = paymentMethod->pay(order->getTotalAmount());

            // Update order status
            if(paid){
                order->setOrderStatus({OrderStatus::Paid, OrderStatus::Shipping});
                cout << "Payment successful. Order is now being processed for delivery." << endl;
                cout << "Please check your email for order details." << endl;
            }
            else{
                if(paymentMethod->getPaymentMethod() == "COD"){
                    order->setOrderStatus({OrderStatus::Confirmed, OrderStatus::COD});
                    cout << "Order confirmed for COD. Amount will be paid upon delivery." << endl;
                    cout << "Please check your email for order details." << endl;
                }
                else{
                order->setOrderStatus({OrderStatus::Confirmed, OrderStatus::Pending});
                cout << "Payment failed. Order status remains pending." << endl;
            }
        }

        } else {
            cout << "You must log in as a customer first." << endl;
        }


    }

    void undo() override {
        if (order != nullptr) {
            order->setOrderStatus({OrderStatus::Pending});
            cout << "Undo: Payment reverted. Order status reset to pending." << endl;
        }
    }
};
