#include "NormalUserState.h"

void NormalUserState::showMenu() {

}

void NormalUserState::addBook(const string& title, const string& genre, int year, const string& publisher, double price, int stock, const vector<string>& authors) {
    cout << "You are not authorized to add books" << endl;
}
void NormalUserState::editBook(string bookId, double price) {
    cout << "You are not authorized to edit books" << endl;
}
void NormalUserState::editBook(string bookId, int stock) {
    cout << "You are not authorized to edit books" << endl;
}
void NormalUserState::deleteBook(string bookId) {
    cout << "You are not authorized to delete books" << endl;
}

void NormalUserState::addAuthor(const string& name) {
    cout << "You are not authorized to add authors" << endl;
}
void NormalUserState::editAuthor(string authorId, const string& name) {
    cout << "You are not authorized to edit authors" << endl;
}
void NormalUserState::deleteAuthor(string authorId) {
    cout << "You are not authorized to delete authors" << endl;
}

void NormalUserState::viewOrders() {
    cout << "You are not authorized to view orders" << endl;
}
void NormalUserState::editOrder(string orderId, OrderStatus status) {
    cout << "You are not authorized to edit orders" << endl;
}
void NormalUserState::cancelOrder(string orderId) {
    cout << "You are not authorized to cancel orders" << endl;
}

void NormalUserState::reportRevenue(const string& period) {
    cout << "You are not authorized to view revenue reports" << endl;
}
void NormalUserState::reportBooksSold(const string& period) {
    cout << "You are not authorized to view books sold reports" << endl;
}
void NormalUserState::reportCustomerCount(const string& period) {
    cout << "You are not authorized to view customer count reports" << endl;
}

void NormalUserState::importBooksFromFile(const string& filename) {
    cout << "You are not authorized to import books" << endl;
}
void NormalUserState::importAuthorsFromFile(const string& filename) {
    cout << "You are not authorized to import authors" << endl;
}
void NormalUserState::importOrdersFromFile(const string& filename) {
    cout << "You are not authorized to import orders" << endl;
}
