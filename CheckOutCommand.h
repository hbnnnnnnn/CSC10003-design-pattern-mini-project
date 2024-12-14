#ifndef CHECKOUTCOMMAND_H
#define CHECKOUTCOMMAND_H

#include "Command.h"
#include "Order.h"
#include "PaymentStrategy.h"
#include "EWallet.h"
#include "BankTransfer.h"
#include "CreditCard.h"
#include "COD.h"

class ManageSys;
class CheckOutCommand : public Command {
private:
    ManageSys* manager;
    Order* order;
    PaymentStrategy* paymentMethod;

public:
    CheckOutCommand(Order* order, PaymentStrategy* paymentMethod)
        : order(order), paymentMethod(paymentMethod) {}

    void execute() override;

    void undo() override;
};

#endif // CHECKOUTCOMMAND_H
