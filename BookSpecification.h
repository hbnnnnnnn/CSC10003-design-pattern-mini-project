#pragma once
#include "Book.h"
#include <algorithm>
#include <string>
#include <vector>
#include "Author.h"

using namespace std;

class BookSpecification {
public:
    virtual ~BookSpecification() = default;
    virtual bool isSatisfied(Book* item) = 0;
};

class BookTitleBookSpecification : public BookSpecification {
    string title;
public:
    BookTitleBookSpecification(const string& title) : title(title) {}
    bool isSatisfied(Book* item) override {
        return item->getName() == title;
    }
};

class BookGenreBookSpecification : public BookSpecification {
    string genre;
public:
    BookGenreBookSpecification(const string& genre) : genre(genre) {}
    bool isSatisfied(Book* item) override {
        return item->getGenre() == genre;
    }
};

class BookAuthorBookSpecification : public BookSpecification {
    string author;
public:
    BookAuthorBookSpecification(const string& author) : author(author) {}
    bool isSatisfied(Book* item) override {
        vector<Author*> authors = item->getAuthors();
        return find(authors.begin(), authors.end(), author) != authors.end();
    }
};

class BookPublisherBookSpecification : public BookSpecification {
    string publisher;
public:
    BookPublisherBookSpecification(const string& publisher) : publisher(publisher) {}
    bool isSatisfied(Book* item) override {
        return item->getPublisher() == publisher;
    }
};

class BookPriceRangeBookSpecification : public BookSpecification {
    double minPrice;
    double maxPrice;
public:
    BookPriceRangeBookSpecification(double minPrice, double maxPrice) 
        : minPrice(minPrice), maxPrice(maxPrice) {}
    bool isSatisfied(Book* item) override {
        double price = item->getPrice();
        return price >= minPrice && price <= maxPrice;
    }
};