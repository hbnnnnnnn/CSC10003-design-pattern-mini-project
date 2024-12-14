#include "ManageSys.h"
#include "AdminUser.h"
#include "OrderUtils.h"

ManageSys* ManageSys::instance = nullptr;

ManageSys::ManageSys() : currentUser(nullptr) {
    adminCredentials["admin1"] = "12345678";
    adminCredentials["admin2"] = "27072005";

    normalUserCredentials["user1"] = "21032005";
    normalUserCredentials["user2"] = "08032005";
}

ManageSys* ManageSys::getInstance() {
    if (!instance) {
        instance = new ManageSys();
    }
    return instance;
}

void ManageSys::destroyInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

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
        } else if (userType == "customer") {
            auto it = normalUserCredentials.find(username);
            if (it != normalUserCredentials.end() && it->second == password) {
                cout << "Customer user login successful!" << endl;
                Customer* customer = new Customer;
                //customer->input();
                currentUser = new NormalUser(username, password, customer);
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
    for(auto& book : books) {
        if(book->getId() == bookId) {
            books.erase(std::remove(books.begin(), books.end(), book), books.end());
            delete book;
            cout << "Book deleted successfully!" << endl;
            return;
        }
    }
}

bool ManageSys::signup(const string &username, const string &password, const string &userType)
{
    if (userType == "admin") {
        auto it = adminCredentials.find(username);
        if (it == adminCredentials.end()) {
            adminCredentials[username] = password;
            currentUser = new AdminUser(username, password);
            cout << "Admin account created successfully!" << endl;
            return true;
        }
    } else if (userType == "customer") {
        auto it = normalUserCredentials.find(username);
        if (it == normalUserCredentials.end()) {
            normalUserCredentials[username] = password;
            Customer* customer = new Customer;
            customer->input();
            currentUser = new NormalUser(username, password, customer);
            cout << "Customer user account created successfully!" << endl;
            return true;
        }
    }
    cout << "Username already exists." << endl;
    return false;
}

void ManageSys::addBook(const string &title, const string &genre, int year, const string &publisher, double price, int stock, const vector<string> &authors)
{
    Book* book = new Book(title, genre, year, publisher, price, stock);
    addBook(book);
    cout << "Book added successfully!" << endl;
}

void ManageSys::editBook(string bookId, double price) {
    Book* book = getBookById(bookId);
    if(book) {
        book->setPrice(price);
        cout << "Book price updated successfully!" << endl;
    }
}

void ManageSys::editBook(string bookId, int stock) {
    Book* book = getBookById(bookId);
    if(book) {
        book->setStock(stock);
        cout << "Book stock updated successfully!" << endl;
    }
}

// Author management
void ManageSys::addAuthor(Author* author) {
    if(author) {
        authors.push_back(author);
        cout << "Author added successfully!" << endl;
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
    for(auto& author : authors) {
        if(author->getId() == authorId) {
            authors.erase(std::remove(authors.begin(), authors.end(), author), authors.end());
            delete author;
            cout << "Author deleted successfully!" << endl;
            return;
        }
    }
}

void ManageSys::addAuthor(const string& name) {
    Author* newAuthor = new Author(name);
    addAuthor(newAuthor);
}

void ManageSys::editAuthor(string authorId, const string& name) {
    Author* author = getAuthorById(authorId);
    if(author) {
        author->setName(name);
        cout << "Author name updated successfully!" << endl;
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
        order->setOrderStatus({status});
        cout << "Order status updated successfully!" << endl;
    }
}

void ManageSys::cancelOrder(string orderId) {
    Order* order = getOrderById(orderId);
    if (order) {
        order->setOrderStatus({OrderStatus::Cancelled});
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

string joinAuthors(const vector<Author*>& authors, const string& delimiter = ", ") {
    ostringstream oss;
    for (size_t i = 0; i < authors.size(); ++i) {
        oss << authors[i];
        if (i < authors.size() - 1) {
            oss << delimiter; // Add delimiter between authors
        }
    }
    return oss.str();
}

void ManageSys::printBooks(vector<Book*> books)
{
    // Define column widths
    const int idWidth = 10;
    const int titleWidth = 30;
    const int authorWidth = 40;
    const int priceWidth = 10;

    // Print table header
    cout << "| " << left << setw(idWidth) << "Ma sach"
         << "| " << setw(titleWidth) << "Ten sach"
         << "| " << setw(authorWidth) << "Tac gia"
         << "| " << setw(priceWidth) << "Gia ban"
         << " |" << endl;
    cout << "|-" << setfill('-') << setw(idWidth) << ""
         << "|-" << setw(titleWidth) << ""
         << "|-" << setw(authorWidth) << ""
         << "|-" << setw(priceWidth) << ""
         << "-|" << setfill(' ') << endl;

    // Print table rows
    for (const auto& book : books) {
        cout << "| " << left << setw(idWidth) << book->getId()
             << "| " << setw(titleWidth) << book->getName()
             << "| " << setw(authorWidth) << joinAuthors(book->getAuthors())
             << "| " << setw(priceWidth) << fixed << setprecision(0) << book->getPrice()
             << " |" << endl;
    }
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

void ManageSys::updateStock(string bookId, int quantity)
{
    Book* book = getBookById(bookId);
    if(book) {
        book->updateStock(quantity);
    }
}

void ManageSys::addOrder(Order *order)
{
    orders.push_back(order);
}

string randomOrderId() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(0));
    string orderId;
    for (int i = 0; i < 6; i++) {
        orderId += chars[rand() % chars.size()];
    }
    return orderId;
}

string getRandomOrderDate(int startYear, int endYear) {
    // Seed the random number generator
    srand(time(0));

    // Generate random year, month, and day
    int year = startYear + rand() % (endYear - startYear + 1);
    int month = 1 + rand() % 12;

    // Determine the number of days in the selected month
    int daysInMonth = 31;
    if (month == 2) {
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            daysInMonth = 29;
        } else {
            daysInMonth = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    }

    int day = 1 + rand() % daysInMonth;

    // Format the date as YYYY-MM-DD
    ostringstream oss;
    oss << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << day;

    return oss.str();
}

Order* ManageSys::createNewOrder(float amount, vector<pair<Book*, int>> productList, Customer* customer) {
    string orderId = randomOrderId();
    time_t now = time(0);
    string orderDate = getRandomOrderDate(2023, 2024);
    OrderStatus status = OrderStatus::Placed;
    Order* order = new Order(orderId, orderDate, amount, {OrderStatus::Placed}, productList, customer);
    return order;
}

void ManageSys::displayOrderDetails(const string& orderID) {
    for (const auto& order : orders) {
        if (order->getOrderID() == orderID) {
            cout << "> Chi tiet don hang " << orderID << ":" << endl;
            cout << "> Ngay dat: " << order->getOrderDate() << endl;

            // Display products
            cout << "> Danh sach san pham:" << endl;
            const int idWidth = 10, nameWidth = 30, qtyWidth = 10, priceWidth = 10, totalWidth = 12;
            cout << "| " << left << setw(idWidth) << "Ma sach"
                 << "| " << setw(nameWidth) << "Ten sach"
                 << "| " << setw(qtyWidth) << "So luong"
                 << "| " << setw(priceWidth) << "Don gia"
                 << "| " << setw(totalWidth) << "Thanh tien"
                 << " |" << endl;

            cout << "|-" << setfill('-') << setw(idWidth) << ""
                 << "|-" << setw(nameWidth) << ""
                 << "|-" << setw(qtyWidth) << ""
                 << "|-" << setw(priceWidth) << ""
                 << "|-" << setw(totalWidth) << ""
                 << "-|" << setfill(' ') << endl;

            for (const auto& product : order->getProductList()) {
                Book* book = product.first;
                int qty = product.second;
                double total = book->getPrice() * qty;

                cout << "| " << left << setw(idWidth) << book->getId()
                     << "| " << setw(nameWidth) << book->getName()
                     << "| " << setw(qtyWidth) << qty
                     << "| " << setw(priceWidth) << fixed << setprecision(0) << book->getPrice()
                     << "| " << setw(totalWidth) << total
                     << " |" << endl;
            }

            // Display total and status
            cout << "> Tong tien: " << fixed << setprecision(0) << order->getTotalAmount() << endl;
            cout << "> Trang thai: " << getStatusAsString(order->getStatus().back()) << endl;
            return;
        }
    }
    cout << "Order not found!" << endl;
}

void ManageSys::updatePassword(const string& username, const string& newPassword, const string& userType) {
    if (userType == "customer") {
        if (normalUserCredentials.find(username) != normalUserCredentials.end()) {
            normalUserCredentials[username] = newPassword;
            cout << "Password updated successfully!" << endl;
        } else {
            cout << "User not found!" << endl;
        }
    } else if (userType == "admin") {
        if (adminCredentials.find(username) != adminCredentials.end()) {
            adminCredentials[username] = newPassword;
            cout << "Password updated successfully!" << endl;
        } else {
            cout << "Admin user not found!" << endl;
        }
    }
}


