#include "ManageSys.h"
#include "Command.h"

class AddToCartCommand : public Command {
private:
    ManageSys* manager;     // Receiver
    string bookId;          // ID of the book to add
    vector<Book*>& cart;    // Reference to the user's cart
    Book* lastAddedBook;    // Stores the last added book for undo

public:
    AddToCartCommand(ManageSys* manager, string bookId, vector<Book*>& cart)
        : manager(manager), bookId(bookId), cart(cart), lastAddedBook(nullptr) {}

    void execute() override {
        if (manager->getCurrentUser() && manager->getCurrentUser()->getType() == "customer") {
            Book* book = manager->getBookById(bookId);
            if (book != nullptr && book->getStock() > 0) {
                book->updateStock(-1);
                cart.push_back(book);
                lastAddedBook = book;
                cout << "Book added to cart." << endl;
            } else {
                cout << "Book not found or out of stock." << endl;
            }
        } else {
            cout << "You must log in as a customer first." << endl;
        }
    }

    void undo() override {
        if (lastAddedBook != nullptr) {
            lastAddedBook->updateStock(1);  // Return the book to stock
            cart.pop_back();                // Remove it from the cart
            cout << "Undo: Book removed from cart." << endl;
        }
    }
};