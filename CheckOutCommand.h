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
    CheckOutCommand(ManageSys* manager, Order* order)
        : manager(manager), order(order), paymentMethod(nullptr) {}

    void execute() override;

    void undo() override;
};

#endif // CHECKOUTCOMMAND_H
