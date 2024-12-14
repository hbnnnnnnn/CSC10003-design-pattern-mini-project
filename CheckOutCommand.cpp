#include "CheckOutCommand.h"
#include "ManageSys.h"


void CheckOutCommand::execute() {
    // Check if the current user is logged in and is a customer
    if (manager->getCurrentUser() && manager->getCurrentUser()->getType() == "customer") {

        // Ensure the order has products
        if (order->getProductList().empty()) {
            cout << "Cart is empty." << endl;
            return;
        }

        // Display order details
        cout << "Order " << order->getOrderID() << " details:" << endl;
        cout << "Order Date: " << order->getOrderDate() << endl;
        cout << "List of products: " << endl;
        order->display();
        cout << "Total: " << order->getTotalAmount() << endl;
        order->displayStatus();

        // Offer payment method choices
        cout << "> Choose a payment method:" << endl;
        cout << "> 1. Credit Card" << endl;
        cout << "> 2. Bank Transfer" << endl;
        cout << "> 3. E-Wallet" << endl;
        cout << "> 4. COD" << endl;
        cout << "> Enter your choice (1-4): ";

        int choice;
        cin >> choice;

        // Validate payment method choice
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
            return;  // Exit if invalid choice is entered
        }

        // Check if payment method is correctly initialized
        if (paymentMethod == nullptr) {
            cout << "Payment method selection failed." << endl;
            return;
        }

        // Input payment details and process payment
        paymentMethod->input();
        bool paid = paymentMethod->pay(order->getTotalAmount());

        // Update order status based on payment result
        if (paid) {
            order->setOrderStatus({ OrderStatus::Paid, OrderStatus::Shipping });
            cout << "Payment successful. Order is now being processed for delivery." << endl;
            cout << "Please check your email for order details." << endl;
        }
        else {
            // Handle failure in non-COD payments
            if (paymentMethod->getPaymentMethod() == "COD") {
                order->setOrderStatus({ OrderStatus::Confirmed, OrderStatus::COD });
                cout << "Order confirmed for COD. Amount will be paid upon delivery." << endl;
                cout << "Please check your email for order details." << endl;
            }
            else {
                order->setOrderStatus({ OrderStatus::Confirmed, OrderStatus::Pending });
                cout << "Payment failed. Order status remains pending." << endl;
            }
        }
        manager->getCurrentUser()->getCustomer()->addOrder(order);
    }
    else {
        cout << "You must log in as a customer first." << endl;
    }
}


void CheckOutCommand::undo() {
    if (order != nullptr) {
        order->setOrderStatus({OrderStatus::Pending});
        cout << "Undo: Payment reverted. Order status reset to pending." << endl;
    }
}
