#include "CancelOrderCommand.h"
#include "OrderUtils.h"

void CancelOrderCommand::execute() {
    if (order->getStatus().back() == OrderStatus::Placed ||
        order->getStatus().back() == OrderStatus::Confirmed) {
        order->setOrderStatus({OrderStatus::Cancelled});
        cout << "Order " << order->getOrderID() << " has been cancelled." << endl;
    } else {
        cout << "Order cannot be cancelled as it is in the '"
             << getStatusAsString(order->getStatus().back()) << "' state." << endl;
    }
}
