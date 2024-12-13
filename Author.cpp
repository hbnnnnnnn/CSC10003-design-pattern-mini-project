#include "Book.h"
#include "Author.h"

void Author::addBook(Book* book) {
    if(book) {
        books.push_back(book);
    }
}

void Author::removeBook(Book* book) {
    books.erase(remove(books.begin(), books.end(), book), books.end());
}

void Author::display() {
    cout << "Author ID: " << id << endl;
    cout << "Author Name: " << name << endl;
    cout << "Books: " << endl;
    for (auto book : books) {
        cout << book->getName() << endl;
    }
}

string Author::getId() {
    return id;
}

string Author::getName() {
    return name;
}

vector<Book*> Author::getBooks() {
    return books;
}

void Author::setId(string id) {
    this->id = id;
}

void Author::setName(string name) {
    this->name = name;
}

void Author::setBooks(vector<Book*> books) {
    this->books = books;
}
