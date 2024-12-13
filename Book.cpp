#include "Author.h"
#include "Book.h"

void Book::addAuthor(Author* author) {
    authors.push_back(author);
}

void Book::removeAuthor(Author* author) {
    authors.erase(remove(authors.begin(), authors.end(), author), authors.end());
}

void Book::display() {
    cout << "Book ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Genre: " << genre << endl;
    cout << "Year: " << year << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Price: " << price << endl;
    cout << "Stock: " << stock << endl;
    cout << "Authors: ";
    for (auto& author : authors) {
        cout << author->getName() << " ";
    }
    cout << endl;
}

string Book::getId()
{
    return id;
}

string Book::getName() {
    return name;
}

string Book::getGenre() {
    return genre;
}

int Book::getYear() {
    return year;
}

string Book::getPublisher() {
    return publisher;
}

float Book::getPrice() {
    return price;
}

int Book::getStock() {
    return stock;
}

vector<Author*> Book::getAuthors() {
    return authors;
}

void Book::setId(string id) {
    this->id = id;
}

void Book::setName(string name) {
    this->name = name;
}

void Book::setGenre(string genre) {
    this->genre = genre;
}

void Book::setYear(int year) {
    this->year = year;
}

void Book::setPublisher(string publisher) {
    this->publisher = publisher;
}

void Book::setPrice(float price) {
    this->price = price;
}

void Book::setStock(int stock) {
    this->stock = stock;
}

void Book::setAuthors(vector<Author*> authors) {
    this->authors = authors;
}