#include "NormalUserState.h"

void NormalUserState::showMenu() {
    ManageSys* manageSys = ManageSys::getInstance();
    vector<Book*> cart;
    CommandInvoker invoker;
    Order* lastOrder = nullptr;

    while (true) {
        cout << "\n> Customer Menu:" << endl;
        cout << "> Search books" << endl;
        cout << "> View <BookID>" << endl;
        cout << "> Add to cart" << endl;
        cout << "> Confirm order" << endl;
        cout << "> Check out" << endl;
        cout << "> Order management" << endl;
        cout << "> Account management" << endl;
        cout << "> Logout" << endl;
        cout << "Enter a command: ";

        string input;
        getline(cin, input);

        if (input.rfind("Search books", 0) == 0) {
            searchBooksMenu(manageSys);
        } else if (input.rfind("View ", 0) == 0) {
            viewBookDetails(input, manageSys);
        } else if (input == "Add to cart") {
            addToCartMenu(manageSys, cart, invoker);
        } else if (input == "Confirm order") {
            confirmationMenu(manageSys, cart, invoker);
        } else if (input == "Check out") {
            checkOutMenu(manageSys, lastOrder, invoker);
        } else if (input == "Order management") {
            if (manageSys->getCurrentUser()->getCustomer()) {
                orderManagementMenu(invoker);
            } else {
                cout << "You must log in as a customer to manage orders." << endl;
            }
        } else if (input == "Account management") {
            accountManagementMenu(manageSys);
        } else if (input == "Logout") {
            cout << "Logging out..." << endl;
            break;
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
}

void NormalUserState::viewBookDetails(const string& command, ManageSys* manageSys) {
    if (command.length() <= 5) {
        cout << "Invalid command format. Use: View <BookID>" << endl;
        return;
    }

    string bookId = command.substr(5); // Extract BookID
    Book* book = manageSys->getBookById(bookId);

    if (book) {
        cout << "\n> Book Details:" << endl;
        book->display();
    } else {
        cout << "Book not found for ID: " << bookId << endl;
    }
}
void NormalUserState::searchBooksMenu(ManageSys* manageSys) {
    while (true) {
        cout << "\n> Book Search:" << endl;
        cout << "    > 1. Search by Title" << endl;
        cout << "    > 2. Search by Genre" << endl;
        cout << "    > 3. Search by Author" << endl;
        cout << "    > 4. Search by Publisher" << endl;
        cout << "    > 5. Search by Price Range" << endl;
        cout << "    > 6. Back" << endl;
        cout << "Enter your choice (1-6): ";

        int choice;
        cin >> choice;

        string input;
        BookSpecification* spec = nullptr;

        switch (choice) {
            case 1: {
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, input);
                spec = new BookTitleBookSpecification(input);
                break;
            }
            case 2: {
                cout << "Enter book genre: ";
                cin.ignore();
                getline(cin, input);
                spec = new BookGenreBookSpecification(input);
                break;
            }
            case 3: {
                cout << "Enter author name: ";
                cin.ignore();
                getline(cin, input);
                spec = new BookAuthorBookSpecification(input);
                break;
            }
            case 4: {
                cout << "Enter publisher name: ";
                cin.ignore();
                getline(cin, input);
                spec = new BookPublisherBookSpecification(input);
                break;
            }
            case 5: {
                double minPrice, maxPrice;
                cout << "Enter minimum price: ";
                cin >> minPrice;
                cout << "Enter maximum price: ";
                cin >> maxPrice;
                spec = new BookPriceRangeBookSpecification(minPrice, maxPrice);
                break;
            }
            case 6:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                continue;
        }

        if (spec) {
            vector<Book*> results = manageSys->searchBooks(spec);
            if (results.empty()) {
                cout << "No books found matching the criteria." << endl;
            } else {
                cout << "\n> Search Results:" << endl;
                manageSys->printBooks(results);
            }
            delete spec;
        }
    }
}

void NormalUserState::addToCartMenu(ManageSys* manageSys, vector<Book*>& cart, CommandInvoker& invoker) {
    while (true) {
        cout << "\n> Add to Cart:" << endl;
        cout << "    > Enter 'Add <BookID>, <Quantity>' to add books to your cart." << endl;
        cout << "    > Enter 'Undo' to remove the last added book." << endl;
        cout << "    > Enter 'Back' to return to the main menu." << endl;
        cout << "Enter command: ";

        string command;
        getline(cin, command);

        if (command == "Back") {
            return;
        } else if (command == "Undo") {
            invoker.undoLastCommand();
        } else if (command.rfind("Add ", 0) == 0) {
            size_t pos = command.find(",");
            if (pos != string::npos) {
                string bookId = command.substr(4, pos - 4);
                int quantity = stoi(command.substr(pos + 1));

                Command* addToCart = new AddToCartCommand(manageSys, bookId, quantity, cart);
                invoker.executeCommand(addToCart);
            } else {
                cout << "Invalid format. Use: Add <BookID>, <Quantity>" << endl;
            }
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
}

void NormalUserState::confirmationMenu(ManageSys* manageSys, vector<Book*>& cart, CommandInvoker& invoker) {
    if (cart.empty()) {
        cout << "Your cart is empty. Add books to your cart first." << endl;
        return;
    }

    Command* confirmation = new ConfirmationCommand(manageSys, cart);
    invoker.executeCommand(confirmation);
}

void NormalUserState::checkOutMenu(ManageSys* manageSys, Order* order, CommandInvoker& invoker) {
    if (!order || order->getProductList().empty()) {
        cout << "Your cart is empty. Please add items before checking out." << endl;
        return;
    }

    cout << "\n> Checkout:" << endl;
    order->display();

    cout << "Choose a payment method:\n";
    cout << "1. Credit Card\n2. Bank Transfer\n3. E-Wallet\n4. COD\n";
    cout << "Enter your choice (1-4): ";

    int choice;
    cin >> choice;

    PaymentStrategy* paymentMethod = nullptr;
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
            cout << "Invalid choice." << endl;
            return;
    }

    paymentMethod->input();
    Command* checkOutCommand = new CheckOutCommand(order, paymentMethod);
    invoker.executeCommand(checkOutCommand);
}


void NormalUserState::accountManagementMenu(ManageSys* manager) {
    if (!customer) {
        cout << "You must log in as a customer to manage your account." << endl;
        return;
    }

    CustomerMemento* backup = customer->save(); // Save the current state of the customer

    while (true) {
        cout << "\n> Account Management:" << endl;
        cout << "    > 1. View Account Details" << endl;
        cout << "    > 2. Edit Account Details" << endl;
        cout << "    > 3. Change Password" << endl;
        cout << "    > 4. Undo Last Change" << endl;
        cout << "    > 5. Back" << endl;
        cout << "Enter your choice (1-5): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: // View Account Details
                customer->display();
                break;

            case 2: { // Edit Account Details
                backup = customer->save(); // Save state before making changes
                string newName, newPhone, newEmail, newAddress;

                cout << "Enter new name (leave blank to keep current): ";
                cin.ignore();
                getline(cin, newName);
                if (!newName.empty()) customer->setName(newName);

                cout << "Enter new phone number (leave blank to keep current): ";
                getline(cin, newPhone);
                if (!newPhone.empty()) customer->setPhoneNumber(newPhone);

                cout << "Enter new email (leave blank to keep current): ";
                getline(cin, newEmail);
                if (!newEmail.empty()) customer->setEmail(newEmail);

                cout << "Enter new shipping address (leave blank to keep current): ";
                getline(cin, newAddress);
                if (!newAddress.empty()) customer->setShippingAddress(newAddress);

                cout << "Account details updated successfully!" << endl;
                customer->display();
                break;
            }

            case 3: // Change Password
                changePassword(manager, manager->getCurrentUser());
                break;

            case 4: // Undo Last Change
                if (backup) {
                    customer->restore(backup);
                    cout << "Changes undone!" << endl;
                    customer->display();
                } else {
                    cout << "No changes to undo." << endl;
                }
                break;

            case 5: // Back
                delete backup; // Cleanup before exiting
                return;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void NormalUserState::changePassword(ManageSys* manager, User* user) {
    string currentPassword, newPassword, confirmPassword;

    cout << "Enter your current password: ";
    cin >> currentPassword;

    if (currentPassword != user->getPassword()) {
        cout << "Incorrect password. Please try again." << endl;
        return;
    }

    cout << "Enter new password: ";
    cin >> newPassword;

    cout << "Confirm new password: ";
    cin >> confirmPassword;

    if (newPassword != confirmPassword) {
        cout << "Passwords do not match. Please try again." << endl;
        return;
    }

    user->setPassword(newPassword);
    manager->updatePassword(user->getUsername(), newPassword, "customer");

    cout << "Password updated successfully!" << endl;
}

void NormalUserState::orderManagementMenu(CommandInvoker& invoker) {
    while (true) {
        cout << "\n> Order Management:" << endl;
        cout << "    > 1. View All Orders" << endl;
        cout << "    > 2. View Order Details" << endl;
        cout << "    > 3. Cancel an Order" << endl;
        cout << "    > 4. Back" << endl;
        cout << "Enter your choice (1-4): ";

        int choice;
        cin >> choice;

        string orderId;
        Order* selectedOrder = nullptr;

        switch (choice) {
            case 1: // View all orders
                invoker.executeCommand(new ViewAllOrdersCommand(customer));
                break;

            case 2: { // View order details
                cout << "Enter Order ID to view details: ";
                cin >> orderId;
                selectedOrder = customer->getOrderById(orderId);
                if (selectedOrder) {
                    invoker.executeCommand(new ViewOrderDetailsCommand(selectedOrder));
                } else {
                    cout << "Order not found!" << endl;
                }
                break;
            }

            case 3: { // Cancel an order
                cout << "Enter Order ID to cancel: ";
                cin >> orderId;
                selectedOrder = customer->getOrderById(orderId);
                if (selectedOrder && 
                    (selectedOrder->getStatus().back() == OrderStatus::Placed || 
                     selectedOrder->getStatus().back() == OrderStatus::Confirmed)) {
                    invoker.executeCommand(new CancelOrderCommand(selectedOrder));
                } else {
                    cout << "Order cannot be canceled (Invalid status or not found)." << endl;
                }
                break;
            }

            case 4: // Back
                return;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}
