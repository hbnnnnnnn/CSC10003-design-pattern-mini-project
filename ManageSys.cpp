#include "ManageSys.h"
#include "AdminUser.h"

void ManageSys::addBook(Book *book)
{
    if(book) {
        books.push_back(book);
    }
}

bool ManageSys::login(const string& username, const string& password, const string& userType) {
    if (userType == "admin") {
            auto it = adminCredentials.find(username);
            if (it != adminCredentials.end() && it->second == password) {
                cout << "Admin login successful!" << endl;
                currentUser = new AdminUser(username, password);  // Assign an Admin object
                return true;
            }
        } else if (userType == "normal") {
            auto it = normalUserCredentials.find(username);
            if (it != normalUserCredentials.end() && it->second == password) {
                cout << "Normal user login successful!" << endl;
                currentUser = new NormalUser(username, password);  // Assign a NormalUser object
                return true;
            }
        }
        cout << "Invalid login credentials." << endl;
        return false;
}

void ManageSys::logout() {
    delete currentUser;
    currentUser = nullptr;
    cout << "Logged out successfully!" << endl;
}

Book* ManageSys::getBookById(string bookId) {
    for(auto& book : books) {
        if(book->getId() == bookId) {
            return book;
        }
    }
    return nullptr;
}

void ManageSys::deleteBook(string bookId) {
    books.erase(std::remove_if(books.begin(), books.end(), [bookId](Book* book) {
        return book->getId() == bookId;
    }), books.end());
}

void ManageSys::addBook(const string& title, const string& genre, int year, const string& publisher, double price, int stock, const vector<string>& authors) {
    Book* book = new Book(title, genre, year, publisher, price, stock);
    addBook(book);
}

void ManageSys::editBook(string bookId, double price) {
    Book* book = getBookById(bookId);
    if(book) {
        book->setPrice(price);
    }
}

void ManageSys::editBook(string bookId, int stock) {
    Book* book = getBookById(bookId);
    if(book) {
        book->setStock(stock);
    }
}

// Author management
void ManageSys::addAuthor(Author* author) {
    if(author) {
        authors.push_back(author);
    }
}

Author* ManageSys::getAuthorById(string authorId) {
    for(auto& author : authors) {
        if(author->getId() == authorId) {
            return author;
        }
    }
    return nullptr;
}

void ManageSys::deleteAuthor(string authorId) {
    authors.erase(std::remove_if(authors.begin(), authors.end(), [authorId](Author* author) {
        return author->getId() == authorId;
    }), authors.end());
}

void ManageSys::addAuthor(const string& name) {
    Author* newAuthor = new Author(name);
    addAuthor(newAuthor);
}

void ManageSys::editAuthor(string authorId, const string& name) {
    Author* author = getAuthorById(authorId);
    if(author) {
        author->setName(name);
    }
}

// Order management
Order* ManageSys::getOrderById(string orderId) {
    for(auto& order : orders) {
        if(order->getOrderID() == orderId) {
            return order;
        }
    }
    return nullptr;
}

void ManageSys::viewOrders() {
    for(auto& order : orders) {
        order->display();
    }
}

void ManageSys::editOrder(string orderId, OrderStatus status) {
    Order* order = getOrderById(orderId);
    if(order) {
        order->setOrderStatus(status);
    }
}

void ManageSys::cancelOrder(string orderId) {
    Order* order = getOrderById(orderId);
    if (order) {
        order->setOrderStatus(OrderStatus::Cancelled);
        cout << "Order cancelled." << endl;
    } else {
        cout << "Order not found." << endl;
    }
}

// Reporting
void ManageSys::reportRevenue(const string& period) {
    double revenue = 0;
    for (Order* order : orders) {
        if (order->getOrderDate() == period) {
            revenue += order->getTotalAmount();
        }
    }
    cout << "Revenue for " << period << ": " << revenue << endl;
}

void ManageSys::reportBooksSold(const string& period) {
    string booksSold = 0;
    for (Order* order : orders) {
        if (order->getOrderDate() == period) {
            booksSold += order->getProductList().size();
        }
    }
    cout << "Books sold for " << period << ": " << booksSold << endl;
}

void ManageSys::reportCustomerCount(const string& period) {
    int customerCount = 0;
    for (Order* order : orders) {
        if (order->getOrderDate() == period) {
            customerCount++;
        }
    }
    cout << "Customer count for " << period << ": " << customerCount << endl;
}

// Importing data
void ManageSys::importBooksFromFile(const string& filename) {
    // Implementation for importing books from file
}

void ManageSys::importAuthorsFromFile(const string& filename) {
    // Implementation for importing authors from file
}

void ManageSys::importOrdersFromFile(const string& filename) {
    // Implementation for importing orders from file
}

vector<Book *> ManageSys::searchBooks(BookSpecification *spec)
{
    vector<Book*> result;
    for(auto& book : books) {
        if(spec->isSatisfied(book)) {
            result.push_back(book);
        }
    }
    return result;
}

ManageSys::~ManageSys()
{
    for(auto& book : books) {
        delete book;
    }
    for(auto& author : authors) {
        delete author;
    }
    for(auto& order : orders) {
        delete order;
    }
    if(currentUser) {
        delete currentUser;
    }
}
