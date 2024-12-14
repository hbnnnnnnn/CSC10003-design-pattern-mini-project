#include "ConfirmationCommand.h"
#include "ManageSys.h"

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

void ConfirmationCommand::execute() {
    if (manager->getCurrentUser() && manager->getCurrentUser()->getType() == "customer") {
        if (cart.empty()) {
            cout << "Cart is empty." << endl;
            return;
        }

        // Convert the cart to a book-count mapping
        vector<pair<Book*, int>> bookCountVector = convertCartToBookCount(cart);

        // Display aggregated cart details
        cout << "\n> Cart Summary:\n";
        const int idWidth = 10, titleWidth = 30, authorWidth = 30, priceWidth = 10, qtyWidth = 10;
        cout << "| " << left << setw(idWidth) << "Book ID"
             << "| " << setw(titleWidth) << "Title"
             << "| " << setw(authorWidth) << "Author"
             << "| " << setw(priceWidth) << "Price"
             << "| " << setw(qtyWidth) << "Qty"
             << " |" << endl;
        cout << "|-" << setfill('-') << setw(idWidth) << ""
             << "|-" << setw(titleWidth) << ""
             << "|-" << setw(authorWidth) << ""
             << "|-" << setw(priceWidth) << ""
             << "|-" << setw(qtyWidth) << ""
             << "-|" << setfill(' ') << endl;

        totalAmount = 0;
        for (const auto& bookCount : bookCountVector) {
            Book* book = bookCount.first;
            int quantity = bookCount.second;

            cout << "| " << left << setw(idWidth) << book->getId()
                 << "| " << setw(titleWidth) << book->getName()
                 << "| " << setw(authorWidth) << book->getAuthors()[0]->getName()  // Assuming one author
                 << "| " << setw(priceWidth) << fixed << setprecision(2) << book->getPrice()
                 << "| " << setw(qtyWidth) << quantity
                 << " |" << endl;

            totalAmount += book->getPrice() * quantity;
        }

        cout << "Total amount: " << totalAmount << endl;
        cout << "Proceed to check out? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();

        if (choice == 'y') {
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


Order* ConfirmationCommand::getLastOrder() const {
    return lastOrder;
}

void ConfirmationCommand::undo() {
    if (lastOrder != nullptr) {
        manager->cancelOrder(lastOrder->getOrderID());
        cout << "Undo: Checkout operation reverted." << endl;
    }
}