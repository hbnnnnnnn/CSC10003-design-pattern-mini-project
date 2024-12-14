#include "ViewAllOrderCommand.h"
#include "Customer.h"
#include "OrderUtils.h"


void ViewAllOrdersCommand::execute() {
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
