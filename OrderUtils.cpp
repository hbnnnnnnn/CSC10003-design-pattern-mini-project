#include "OrderUtils.h"

string getStatusAsString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Placed: return "Placed";
        case OrderStatus::Confirmed: return "Confirmed";
        case OrderStatus::Paid: return "Paid";
        case OrderStatus::Shipping: return "Shipping";
        case OrderStatus::COD: return "COD";
        case OrderStatus::Pending: return "Pending";
        case OrderStatus::Delivered: return "Delivered";
        case OrderStatus::Cancelled: return "Cancelled";
        default: return "Unknown";
    }
}