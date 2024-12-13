#include "ManageSys.h"
#include "Command.h"

vector<pair<Book*, int>> convertCartToBookCount(const vector<Book*>& cart) {
    unordered_map<Book*, int> bookCountMap;
    for (auto book : cart) {
        bookCountMap[book]++;
    }

    vector<pair<Book*, int>> bookCountVector;
    for (const auto& entry : bookCountMap) {
        bookCountVector.push_back(entry);
    }

    return bookCountVector;
}

class ConfirmationCommand : public Command {
private:
    ManageSys* manager;      // Receiver
    vector<Book*>& cart;     // Reference to the user's cart
    float totalAmount;       // Total cost of the books in the cart
    Order* lastOrder;        // Stores the last created order for undo

public:
    ConfirmationCommand(ManageSys* manager, vector<Book*>& cart)
        : manager(manager), cart(cart), totalAmount(0), lastOrder(nullptr) {}

    void execute() override {
        if (manager->getCurrentUser() && manager->getCurrentUser()->getType() == "customer") {
            if (cart.empty()) {
                cout << "Cart is empty." << endl;
                return;
            }

            manager->printBooks(cart);

            manager->getCurrentUser()->getCustomer()->display();

            totalAmount = 0;
            for (auto book : cart) {
                totalAmount += book->getPrice();
            }

            cout << "Total amount: " << totalAmount << endl;
            cout << "Proceed to check out? (y/n): ";
            char choice;
            cin >> choice;

            if (choice == 'y') {
                vector<pair<Book*, int>> bookCountVector = convertCartToBookCount(cart);
                lastOrder = manager->createNewOrder(totalAmount, bookCountVector, manager->getCurrentUser()->getCustomer());
                manager->addOrder(lastOrder);
                cout << "Confirmation successful. Order id: " << lastOrder->getOrderID() << endl;
                cart.clear();
            } else {
                cout << "Confirmation cancelled." << endl;
            }
        } else {
            cout << "You must log in as a customer first." << endl;
        }
    }

    Order* getLastOrder() const override {
        return lastOrder;
    }

    void undo() override {
        if (lastOrder != nullptr) {
            manager->cancelOrder(lastOrder->getOrderID());
            cout << "Undo: Checkout operation reverted." << endl;
        }
    }
};
