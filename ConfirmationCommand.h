#ifndef CONFIRMATIONCOMMAND_H
#define CONFIRMATIONCOMMAND_H

#include "Command.h"
#include "Book.h"

class ManageSys;

class ConfirmationCommand : public Command {
private:
    ManageSys* manager;      // Receiver
    vector<Book*>& cart;     // Reference to the user's cart
    float totalAmount;       // Total cost of the books in the cart
    Order* lastOrder;        // Stores the last created order for undo

public:
    ConfirmationCommand(ManageSys* manager, vector<Book*>& cart)
        : manager(manager), cart(cart), totalAmount(0), lastOrder(nullptr) {}

    void execute() override;

    Order* getLastOrder() const override;

    void undo() override;
};

#endif // CONFIRMATIONCOMMAND_H
