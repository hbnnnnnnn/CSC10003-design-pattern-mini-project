#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Author;
class Book {
    string id;
    string name;
    string genre;
    int year;
    string publisher;
    float price;
    int stock;
    string description;
    vector<Author*> authors;
public:
    Book() = default;
    Book(string id, string name, string genre, int year, string publisher, float price, int stock, string description) : id(id), name(name), genre(genre), year(year), publisher(publisher), price(price), stock(stock), description(description) {}
    Book(string id, string name, string genre, int year, string publisher, float price, int stock) : id(id), name(name), genre(genre), year(year), publisher(publisher), price(price), stock(stock) {}
    Book(string name, string genre, int year, string publisher, float price, int stock) : Book("", name, genre, year, publisher, price, stock) {}
    void addAuthor(Author* author);
    void removeAuthor(Author* author);
    void display();
    string getId();
    string getName();
    string getGenre();
    int getYear();
    string getPublisher();
    float getPrice();
    int getStock();
    vector<Author*> getAuthors();
    void setId(string id);
    void setName(string name);
    void setGenre(string genre);
    void setYear(int year);
    void setPublisher(string publisher);
    void setPrice(float price);
    void setStock(int stock);
    void setAuthors(vector<Author*> author);
    void updateStock(int quantity);
};