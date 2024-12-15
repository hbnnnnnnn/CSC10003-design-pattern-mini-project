#include "ManageSys.h"
#include "AdminUser.h"
#include "OrderUtils.h"

ManageSys* ManageSys::instance = nullptr;

ManageSys::ManageSys() : currentUser(nullptr) {
    // Admin credentials
    adminCredentials["admin1"] = "12345678";
    adminCredentials["admin2"] = "27072005";

    // Authors
    authors.push_back(new Author("A001", "J.K. Rowling"));
    authors.push_back(new Author("A002", "George R.R. Martin"));
    authors.push_back(new Author("A003", "J.R.R. Tolkien"));
    authors.push_back(new Author("A004", "Brandon Sanderson"));
    authors.push_back(new Author("A005", "Neil Gaiman"));
    authors.push_back(new Author("A006", "Patrick Rothfuss"));

    // Books
    books.push_back(new Book("B001", "Harry Potter", "Fantasy", 2000, "Bloomsbury", 39.9, 100, "A young wizard's journey at Hogwarts.", { authors[0] }));
    books.push_back(new Book("B002", "Game of Thrones", "Fantasy", 1996, "Bantam Books", 29.9, 50, "A tale of power, betrayal, and war in Westeros.", { authors[1] }));
    books.push_back(new Book("B003", "The Hobbit", "Fantasy", 1937, "George Allen & Unwin", 49.9, 80, "A hobbit's epic adventure to reclaim a treasure.", { authors[2] }));
    books.push_back(new Book("B004", "Mistborn", "Fantasy", 2006, "Tor Books", 19.99, 150, "A world of ash and mist, where the oppressed rebel.", { authors[3] }));
    books.push_back(new Book("B005", "American Gods", "Fantasy", 2001, "HarperCollins", 24.99, 120, "A battle between old and new gods in America.", { authors[4] }));
    books.push_back(new Book("B006", "The Name of the Wind", "Fantasy", 2007, "DAW Books", 29.99, 90, "A tale of a legendary figure in a world of magic.", { authors[6] }));
    books.push_back(new Book("B007", "The Stormlight Archive", "Fantasy", 2010, "Tor Books", 49.99, 200, "An epic saga of war, honor, and magic.", { authors[3], authors[4] }));
    books.push_back(new Book("B008", "Neverwhere", "Urban Fantasy", 1996, "Hodder & Stoughton", 19.99, 75, "A journey through a hidden world beneath London.", { authors[5] }));

    // Customers and credentials
    Customer* cust1 = new Customer("C001", "John Doe", "123456789", "john@example.com", "123 Main St");
    Customer* cust2 = new Customer("C002", "Jane Smith", "987654321", "jane@example.com", "456 Elm St");
    customerData["user1"] = cust1;
    customerCredentials["user1"] = "21032005";
    customerData["user2"] = cust2;
    customerCredentials["user2"] = "08032005";

    // Orders
    vector<pair<Book*, int>> orderProducts1 = { { books[0], 2 }, { books[1], 1 } };
    Order* order1 = new Order("O001", "2024-12-10", 129.97, { OrderStatus::Placed }, orderProducts1, cust1);
    orders.push_back(order1);
    cust1->addOrder(order1);

    vector<pair<Book*, int>> orderProducts2 = { { books[2], 1 }, { books[5], 1 } };
    Order* order2 = new Order("O002", "2024-12-11", 59.99, { OrderStatus::Placed }, orderProducts2, cust2);
    orders.push_back(order2);
    cust2->addOrder(order2);
}


ManageSys* ManageSys::getInstance() {
    if (!instance) {
        instance = new ManageSys();
    }
    return instance;
}

void ManageSys::destroyInstance() {
    if (instance) {
        cout << "ManaSys Instance destroyed" << endl;
        delete instance;
        instance = nullptr;
    }
}

void ManageSys::addBook(Book *book)
{
    if(book) {
        books.push_back(book);
        cout << "Book added successfully!" << endl;
    }
}

bool ManageSys::signup(const string& username, const string& password, const string& userType) {
    if (userType == "admin") {
        if (adminCredentials.find(username) == adminCredentials.end()) {
            adminCredentials[username] = password;
            currentUser = new AdminUser(username, password);
            cout << "Admin account created successfully!" << endl;
            return true;
        }
    } else if (userType == "customer") {
        if (customerData.find(username) == customerData.end()) {
            Customer* customer = new Customer;
            customer->input();
            customerData[username] = customer;
            customerCredentials[username] = password;
            currentUser = new NormalUser(username, password, customer);
            cout << "Customer user account created successfully!" << endl;
            return true;
        }
    }
    cout << "Username already exists." << endl;
    return false;
}

bool ManageSys::login(const string& username, const string& password, const string& userType) {
    if (userType == "admin") {
        auto it = adminCredentials.find(username);
        if (it != adminCredentials.end() && it->second == password) {
            cout << "Admin login successful!" << endl;
            currentUser = new AdminUser(username, password);
            return true;
        }
    } else if (userType == "customer") {
        auto it = customerCredentials.find(username);
        if (it != customerCredentials.end() && it->second == password) {
            cout << "Customer user login successful!" << endl;
            currentUser = new NormalUser(username, password, customerData[username]);
            return true;
        }
    }
    cout << "Invalid login credentials." << endl;
    return false;
}

void ManageSys::logout() {
    if (currentUser) {
        delete currentUser;
        currentUser = nullptr;
    }
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
    int booksSold = 0;
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

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Importing data
void ManageSys::importBooksFromFile(const string& filename) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    // Skip the header line
    getline(file, line);

    while (getline(file, line)) {
        vector<string> fields = split(line, ',');
        if(fields.size() < 9) {
            cout << "Invalid book data: " << line << endl;
            continue;
        }
        string bookId = fields[0];
        string name = fields[1];
        string genre = fields[2];
        int year = stoi(fields[3]);
        string publisher = fields[4];
        double price = stod(fields[5]);
        int stock = stoi(fields[6]);
        string description = fields[7];

        // Split authors string into author ids
        vector<string> authorIds = split(fields[8], ',');
        vector<Author*> authors;
        for (const auto& authorId : authorIds) {
            Author* author = getAuthorById(authorId);
            if (author) {
                authors.push_back(author);
            } else {
                cout << "Author ID not found: " << authorId << endl;
            }
        }

        // Create a new Book and add to the list
        Book* book = new Book(bookId, name, genre, year, publisher, price, stock, description, authors);
        addBook(book);  // Assuming addBook() handles adding to the vector
    }

    file.close();
}


void ManageSys::importAuthorsFromFile(const string& filename) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    // Skip the header line
    getline(file, line);

    while (getline(file, line)) {
        vector<string> fields = split(line, ',');
        if(fields.size() < 3) {
            cout << "Invalid author data: " << line << endl;
            continue;
        }
        string authorId = fields[0];
        string name = fields[1];

        // Create a new Author and add to the list
        Author* author = new Author(authorId, name);
        addAuthor(author);  // Assuming addAuthor() handles adding to the vector

        // Associate books with the author
        vector<string> bookIds = split(fields[2], ',');
        for (const auto& bookId : bookIds) {
            Book* book = getBookById(bookId);
            if (book) {
                author->addBook(book);
            } else {
                cout << "Book ID not found: " << bookId << endl;
            }
        }
    }

    file.close();
}

void ManageSys::importOrdersFromFile(const string& filename) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    // Skip the header line
    getline(file, line);

    while (getline(file, line)) {
        vector<string> fields = split(line, ',');

        if (fields.size() < 6) {
            cout << "Invalid order data: " << line << endl;
            continue;
        }

        string orderId = fields[0];
        string orderDate = fields[1];
        float totalAmount = 0.0;
        try {
            totalAmount = stof(fields[2]);
        } catch (const exception& e) {
            cout << "Invalid totalAmount in order: " << line << endl;
            continue;
        }

        vector<string> statusStrs = split(fields[3], '|');
        vector<OrderStatus> status;
        for (const auto& statusStr : statusStrs) {
            if (statusStr == "Placed") status.push_back(OrderStatus::Placed);
            else if (statusStr == "Confirmed") status.push_back(OrderStatus::Confirmed);
            else if (statusStr == "Paid") status.push_back(OrderStatus::Paid);
            else if (statusStr == "Shipping") status.push_back(OrderStatus::Shipping);
            else if (statusStr == "Cancelled") status.push_back(OrderStatus::Cancelled);
            else {
                cout << "Unknown status: " << statusStr << " in order: " << line << endl;
            }
        }

        vector<pair<Book*, int>> productList;
        vector<string> products = split(fields[4], '|'); // Split products by '|'
        for (const auto& product : products) {
            vector<string> productDetails = split(product, ':'); // Split product details by ':'

            if (productDetails.size() != 2) {
                cout << "Invalid product format in order: " << line << endl;
                cout << "Product field: " << product << endl;
                continue;
            }

            Book* book = getBookById(productDetails[0]);
            if (!book) {
                cout << "Book ID not found: " << productDetails[0] << " in order: " << line << endl;
                continue;
            }

            int quantity = 0;
            try {
                quantity = stoi(productDetails[1]);
            } catch (const exception& e) {
                cout << "Invalid quantity for book: " << productDetails[0] << " in order: " << line << endl;
                continue;
            }

            productList.push_back({book, quantity});
        }

        if (customerData.find(fields[5]) == customerData.end()) {
            cout << "Customer ID not found: " << fields[5] << " in order: " << line << endl;
            continue;
        }
        Customer* customer = customerData[fields[5]];

        Order* order = new Order(orderId, orderDate, totalAmount, status, productList, customer);
        addOrder(order);
    }

    file.close();
}


vector<Book*> ManageSys::searchBooks(BookSpecification* spec) {
    vector<Book*> result;
    // Ensure that books are non-null and spec is valid
    for (Book* book : books) {
        if (book && spec->isSatisfied(book)) {
            result.push_back(book);
        }
    }
    return result;
}

string joinAuthors(const vector<Author*>& authors, const string& delimiter = ", ") {
    ostringstream oss;
    for (size_t i = 0; i < authors.size(); ++i) {
        if (authors[i]) { // Null check for Author pointer
            oss << authors[i]->getName();
            if (i < authors.size() - 1) {
                oss << delimiter; // Add delimiter between authors
            }
        }
    }
    return oss.str().empty() ? "Unknown" : oss.str(); // Return "Unknown" if no authors
}

void ManageSys::printBooks(vector<Book*> books) {
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
        if (!book) { // Null check for Book pointer
            cout << "| " << left << setw(idWidth) << "N/A"
                 << "| " << setw(titleWidth) << "N/A"
                 << "| " << setw(authorWidth) << "N/A"
                 << "| " << setw(priceWidth) << "N/A"
                 << " |" << endl;
            continue;
        }

        string bookId = book->getId().empty() ? "Unknown" : book->getId();
        string bookName = book->getName().empty() ? "Unknown" : book->getName();
        string authors = joinAuthors(book->getAuthors());
        double price = book->getPrice();
        
        cout << "| " << left << setw(idWidth) << bookId
             << "| " << setw(titleWidth) << bookName
             << "| " << setw(authorWidth) << authors
             << "| " << setw(priceWidth) << fixed << setprecision(2) << (price > 0 ? price : 0.0)
             << " |" << endl;
    }
}

ManageSys::~ManageSys()
{
    for (auto& customer : customers) {
        delete customer;
        customer = nullptr;
    }
    for(auto& book : books) {
        delete book;
        book = nullptr;
    }
    for(auto& author : authors) {
        delete author;
        author = nullptr;
    }
    for(auto& order : orders) {
        delete order;
        order = nullptr;
    }
    if(currentUser) {
        delete currentUser;
        currentUser = nullptr;
    }
    authors.clear();
    books.clear();
    customers.clear();
    orders.clear();
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
    if (order) {
        orders.push_back(order);
        cout << "Order added successfully!" << endl;
    }

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
    if (!customer) {
        cout << "Error: Customer is null during order creation." << endl;
        return nullptr;
    }
    string orderId = randomOrderId();
    string orderDate = getRandomOrderDate(2023, 2024);
    vector<OrderStatus> status = {OrderStatus::Placed};
    return new Order(orderId, orderDate, amount, status, productList, customer);
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
        if (customerCredentials.find(username) != customerCredentials.end()) {
            customerCredentials[username] = newPassword;
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


