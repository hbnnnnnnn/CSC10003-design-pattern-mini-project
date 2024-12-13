#include "ManageSys.h"
#include "Command.h"

class CheckoutCommand : public Command {
private:
    ManageSys* manager;      // Receiver
    vector<Book*>& cart;     // Reference to the user's cart
    float totalAmount;       // Total cost of the books in the cart
    Order* lastOrder;        // Stores the last created order for undo

public:
    CheckoutCommand(ManageSys* manager, vector<Book*>& cart)
        : manager(manager), cart(cart), totalAmount(0), lastOrder(nullptr) {}

    void execute() override {
        if (manager->getCurrentUser() && manager->getCurrentUser()->getType() == "customer") {
            if (cart.empty()) {
                cout << "Cart is empty." << endl;
                return;
            }

            totalAmount = 0;
            for (auto book : cart) {
                totalAmount += book->getPrice();
            }

            cout << "Total amount: " << totalAmount << endl;
            cout << "Proceed to check out? (y/n): ";
            char choice;
            cin >> choice;

            if (choice == 'y') {
                lastOrder = manager->createNewOrder(totalAmount, cart, manager->getCurrentUser()->getCustomer());
                manager->addOrder(lastOrder);
                cout << "Checkout successful!" << endl;
                cart.clear();
            } else {
                cout << "Checkout cancelled." << endl;
            }
        } else {
            cout << "You must log in as a customer first." << endl;
        }
    }

    void undo() override {
        if (lastOrder != nullptr) {
            manager->cancelOrder(lastOrder->getOrderID());
            cout << "Undo: Checkout operation reverted." << endl;
        }
    }
};
