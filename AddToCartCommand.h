#ifndef ADDTOCARTCOMMAND_H
#define ADDTOCARTCOMMAND_H

#include "Command.h"
#include <vector>
#include <string>
using namespace std;


class ManageSys;

class AddToCartCommand : public Command {
private:
    ManageSys* manager;     // Receiver
    string bookId;          // ID of the book to add
    int amount;             // Amount of the book to add
    vector<Book*>& cart;    // Reference to the user's cart
    Book* lastAddedBook;    // Stores the last added book for undo

public:
    AddToCartCommand(ManageSys* manager, string bookId, int amount, vector<Book*>& cart)
        : manager(manager), bookId(bookId), amount(amount), cart(cart), lastAddedBook(nullptr) {}

    void execute() override;
    void undo() override;
};

#endif // ADDTOCARTCOMMAND_H
