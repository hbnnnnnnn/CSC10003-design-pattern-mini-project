#include "AddToCartCommand.h"
#include "ManageSys.h"
#include "Book.h"

void AddToCartCommand::execute() {
    if (manager->getCurrentUser() && manager->getCurrentUser()->getType() == "customer") {
        Book* book = manager->getBookById(bookId);
        if (book != nullptr && book->getStock() >= amount) {
            book->updateStock(-amount);
            while (amount--) {
                cart.push_back(book);
            }
            lastAddedBook = book;
            cout << "Book added to cart." << endl;
        } else {
            cout << "Book not found or out of stock." << endl;
        }
    } else {
        cout << "You must log in as a customer first." << endl;
    }
}

void AddToCartCommand::undo() {
    if (lastAddedBook != nullptr) {
        lastAddedBook->updateStock(1);
        cart.pop_back();
        cout << "Undo: Book removed from cart." << endl;
    }
}
