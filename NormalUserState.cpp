#include "NormalUserState.h"
#include <iomanip>

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
        cout << "> Logout" << endl;
        cout << "Enter a command (e.g., 'Search books', 'View B001', 'Check out', or 'Logout'): ";

        string input;
        getline(cin, input);

        if (input.rfind("Search books", 0) == 0) {
            searchBooksMenu(manageSys);
        } 
        else if (input.rfind("View ", 0) == 0) {
            viewBookDetails(input, manageSys);
        } 
        else if (input == "Add to cart") {
            addToCartMenu(manageSys, cart, invoker);
        } 
        else if (input == "Confirm order") {
            if (!cart.empty()) {
                Command* confirmationCommand = new ConfirmationCommand(manageSys, cart);
                invoker.executeCommand(confirmationCommand);
                lastOrder = confirmationCommand->getLastOrder(); // Get the created order
            } else {
                cout << "Your cart is empty. Add items before confirming the order." << endl;
            }
        }
        else if (input == "Order management") 
        {
            Customer* customer = manageSys->getCurrentUser()->getCustomer();
            if (customer) {
                orderManagementMenu(customer, invoker);
            } else {
                cout << "You must log in as a customer to view orders." << endl;
            }
        }
 
        else if (input == "Check out") {
            checkOutMenu(manageSys, lastOrder, invoker);
        }
        else if (input == "Account management") {
            accountManagementMenu(manageSys, manageSys->getCurrentUser());
        }

        else if (input == "Logout") {
            cout << "Logging out..." << endl;
            break;
        } 
        else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
}


void NormalUserState::viewBookDetails(const string& command, ManageSys* manageSys) {
    // Ensure the command has the required length to contain "View " and a book ID
    if (command.length() <= 5) {
        cout << "Invalid command format. Use: View <BookID>" << endl;
        return;
    }

    // Extract the Book ID from the command
    string bookId = command.substr(5); // Extract everything after "View "

    // Fetch the book using the ID
    Book* book = manageSys->getBookById(bookId);

    // Display book details or an error message if not found
    if (book != nullptr) {
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
            case 1: // Search by Title
                cout << "> Enter book title: ";
                cin.ignore();
                getline(cin, input);
                spec = new BookTitleBookSpecification(input);
                break;
            case 2: // Search by Genre
                cout << "> Enter book genre: ";
                cin.ignore();
                getline(cin, input);
                spec = new BookGenreBookSpecification(input);
                break;
            case 3: // Search by Author
                cout << "> Enter author name: ";
                cin.ignore();
                getline(cin, input);
                spec = new BookAuthorBookSpecification(input);
                break;
            case 4: // Search by Publisher
                cout << "> Enter publisher name: ";
                cin.ignore();
                getline(cin, input);
                spec = new BookPublisherBookSpecification(input);
                break;
            case 5: { // Search by Price Range
                double minPrice, maxPrice;
                cout << "> Enter minimum price: ";
                cin >> minPrice;
                cout << "> Enter maximum price: ";
                cin >> maxPrice;
                spec = new BookPriceRangeBookSpecification(minPrice, maxPrice);
                break;
            }
            case 6: // Back
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
                cout << "> Search Results:" << endl;
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
        cout << "    > Enter 'Undo' to remove the last added book from the cart." << endl;
        cout << "    > Enter 'Back' to return to the previous menu." << endl;
        cout << "Enter command: ";

        string command;
        getline(cin, command);

        if (command == "Back") {
            return; // Exit the menu
        } else if (command == "Undo") {
            invoker.undoLastCommand(); // Undo the last command
        } else if (command.rfind("Add ", 0) == 0) {
            // Parse the Add command
            size_t pos = command.find(",");
            if (pos != string::npos) {
                string bookId = command.substr(4, pos - 4); // Extract book ID
                int quantity = stoi(command.substr(pos + 1)); // Extract quantity

                // Create and execute the AddToCartCommand
                Command* addToCart = new AddToCartCommand(manageSys, bookId, quantity, cart);
                invoker.executeCommand(addToCart);
            } else {
                cout << "Invalid command format. Use: Add <BookID>, <Quantity>" << endl;
            }
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
}


void NormalUserState::confirmationMenu(ManageSys* manageSys, vector<Book*>& cart, CommandInvoker& invoker) {
    if (cart.empty()) {
        cout << "\nYour cart is empty. Add books to your cart first." << endl;
        return;
    }

    // Create and execute the ConfirmationCommand
    Command* confirmation = new ConfirmationCommand(manageSys, cart);
    invoker.executeCommand(confirmation);
}

void NormalUserState::accountManagementMenu(ManageSys* manager, User* user) {
    Customer* customer = user->getCustomer();
    if (!customer) {
        cout << "You must log in as a customer to manage your account." << endl;
        return;
    }

    // Create a backup of the customer's current state
    CustomerMemento* backup = customer->save();

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
                backup = customer->save(); // Save a new backup before changes
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
                changePassword(manager, user);
                break;

            case 4: { // Undo Last Change
                if (backup) {
                    customer->restore(backup); // Restore the previous state
                    cout << "Changes undone!" << endl;
                    customer->display();
                } else {
                    cout << "No changes to undo." << endl;
                }
                break;
            }

            case 5: // Back
                delete backup; // Clean up the backup when exiting
                return;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}


void NormalUserState::checkOutMenu(ManageSys* manageSys, Order* order, CommandInvoker& invoker) {
    if (order == nullptr || order->getProductList().empty()) {
        cout << "Your cart is empty. Please add items to your cart before checking out." << endl;
        return;
    }

    // Display the order details
    cout << "\n> Checkout:" << endl;
    cout << "Order ID: " << order->getOrderID() << endl;
    order->display();

    // Ask the user to choose a payment method
    cout << "> Choose a payment method:" << endl;
    cout << "> 1. Credit Card" << endl;
    cout << "> 2. Bank Transfer" << endl;
    cout << "> 3. E-Wallet" << endl;
    cout << "> 4. COD" << endl;
    cout << "> Enter your choice (1-4): ";

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
            cout << "Invalid choice. Please try again." << endl;
            return;
    }

    paymentMethod->input(); // Input additional details for the payment method

    // Create and execute the CheckOutCommand
    Command* checkOutCommand = new CheckOutCommand(order, paymentMethod);
    invoker.executeCommand(checkOutCommand);
}


string getStatusAsString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Placed: return "Da dat";
        case OrderStatus::Confirmed: return "Da xac nhan";
        case OrderStatus::Paid: return "Da thanh toan";
        case OrderStatus::Shipping: return "Dang giao";
        case OrderStatus::COD: return "COD";
        case OrderStatus::Pending: return "Dang xu ly";
        case OrderStatus::Delivered: return "Da giao";
        case OrderStatus::Cancelled: return "Da huy";
        default: return "Unknown";
    }
}

void NormalUserState::orderManagementMenu(Customer* customer, CommandInvoker& invoker) {
    while (true) {
        cout << "\n> Order Management:" << endl;
        cout << "    > 1. View all orders" << endl;
        cout << "    > 2. View order details" << endl;
        cout << "    > 3. Cancel an order" << endl;
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

            case 2: // View order details
                cout << "Enter Order ID to view details: ";
                cin >> orderId;
                selectedOrder = customer->getOrderById(orderId);
                invoker.executeCommand(new ViewOrderDetailsCommand(selectedOrder));
                break;

            case 3: // Cancel an order
                cout << "Enter Order ID to cancel: ";
                cin >> orderId;
                selectedOrder = customer->getOrderById(orderId);
                invoker.executeCommand(new CancelOrderCommand(selectedOrder));
                break;

            case 4: // Back
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

