#ifndef AUTHOR_H
#define AUTHOR_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book;
class Author {
    string id;
    string name;
    vector<Book*> books;
public:
    Author() {};
    Author(string name) : name(name) {}
    Author(string id, string name) : id(id), name(name) {}
    void addBook(Book* book);
    void removeBook(Book* book);
    void display();
    string getId();
    string getName();
    vector<Book*> getBooks();
    void setId(string id);
    void setName(string name);
    void setBooks(vector<Book*> books);
};

#endif // AUTHOR_H
